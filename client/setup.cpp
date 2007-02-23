#include "client.hpp"

// Private headers
#include "setup.hpp"
#include "SurfaceLoader.hpp"

struct GameData *setup(struct InitData *d) { return &setup(*d); }
struct GameData &setup(struct InitData &d) {
	GameData &r = *new GameData;
	// Libraries setup
	libs_setup(d, r);
	// Set starting time
	d.startingTime = getTimestamp();
	// Set up screen
	screen_setup(d, r);
	// Create and get Animation Data
	r.animdata = setup_animations(d.animsetup);
	// Fetch special sprites -- no aliases at this point!
	fetch_special_sprites(d, r);
	// Create Actor Movements for special sprites
	aktor_movements_setup(d, r);
	// Create special sprite aliases
	ss_aliases_setup(d, r);
	// Set up AI
	ai_setup(d, r);
	// Set up collision pairs
	collision_setup(d, r);
	// Set up bg colour
	r.bg = SDL_MapRGB(r.screen->format, d.bg.r, d.bg.g, d.bg.b);
	// Set after move callback for animators
	AnimatorHolder::setAfterMoveCall(&d.callbacks->get_amc());
	// Set up teleportation waypoints
	teleportals_setup(d, r);
	// Let game data have access to the collision checker instance
	r.cc = d.cc;

	return r;
} // setup

static void libs_setup(struct InitData const&d, struct GameData &r) {
	db("Initialise SDL");
	nf(SDL_Init(d.sdlflags), "SDL Init");
	db("Initialise TTF");
	nf(TTF_Init(), "TTF Init");
} // independent_setup

static void screen_setup(struct InitData const&d, struct GameData &r) {
	r.screen = SDL_SetVideoMode(
	 d.screen.width,
	 d.screen.height,
	 d.screen.bpp,
	 d.screen.flags
	);
} // screen_setup

static void fetch_special_sprites(struct InitData const&d,
 struct GameData &r)
{
	register size_t i = 0;
	std::vector<spriteid_t>::const_iterator ite;
	r.sss.assign(d.speeds.size(), static_cast<GameSprite*>(0));
	for (ite = d.speeds.begin(); ite != d.speeds.end(); ite++) {
		r.sss[i++] = dynamic_cast<GameSprite*>(
		 r.animdata->spritehold->getSprite(*ite));
		nf(!r.sss[i-1], "Special sprite is not a GameSprite");
	}
} // fetch_special_sprites

static void aktor_movements_setup(struct InitData const&d,
 struct GameData&r)
{
	// For each special sprite create an ActorMovement with
	// appropriate animations (found in anids)
	SSAMS ssams(d, r);
	std::for_each(r.sss.begin(), r.sss.end(), ssams);
} // aktor_movements_setup

// SSAMS - Special Sprite Actor Movement Setup
void SSAMS::operator() (GameSprite *g) {
	// Check that there are more anids for this sprite
	nf(!(anids != d.anids.end()),
	 "Not enough Animation IDs for all special sprites");
	
	// Fetch moving animations
	std::list<MovingAnimation*> mv;
	MovingAnimationFetcher maf(d, r, mv);
	std::for_each(anids->mv.begin(), anids->mv.end(), maf);

	// Fetch frame range animations
	std::list<FrameRangeAnimation*> fr;
	FrameRangeAnimationFetcher fraf(d, r, fr);
	std::for_each(anids->fr.begin(), anids->fr.end(), fraf);

	// Create and start animators
	std::vector<MovingAnimator*> mvtors;
	std::vector<FrameRangeAnimator*> frtors;
	AnimatorSetup torset(d, r, g, mvtors, frtors);
	std::for_each(mv.begin(), mv.end(), torset);
	std::for_each(fr.begin(), fr.end(), torset);

	// Create Actor Movement
	r.akmovs[g] = (new ActorMovement(g, mvtors, frtors,
	 d.callbacks->get_amc(), d.startingTime));

	// Advance iterator
	anids++;
} // SSAMS::()

// Moving Animation Fetcher
void MovingAnimationFetcher::operator() (animid_t const &id) {
	mv.push_back(r.animdata->animhold->getMovingAnimation(id));
} // MovingAnimationFetcher::()

// Frame Range Animation Fetcher
void FrameRangeAnimationFetcher::operator() (animid_t const &id) {
	fr.push_back(r.animdata->animhold->getFrameRangeAnimation(id));
} // FrameRangeAnimationFethcer::()

// Animator Setup
void AnimatorSetup::operator() (Animation* anim) {
	nf(!anim, "NULL animation pointer -- check inits");
	if (MovingAnimation *mv = dynamic_cast<MovingAnimation*>(anim)) {
		// Create animator and do not register with Holder
		mvtors.push_back(new MovingAnimator(false));
		// Start with given sprite and animation
		mvtors.back()->Start(g, mv, d.startingTime);
	} else if (FrameRangeAnimation *fr =
	 dynamic_cast<FrameRangeAnimation*> (anim))
	{
		// Create animator and do not register with Holder
		frtors.push_back(new FrameRangeAnimator(false));
		// Start with given sprite and animation
		frtors.back()->Start(g, fr, d.startingTime);
	} else
		nf(-1, "Unknown animation type");
} // AnimatorSetup::()

#define CAST_GHOST(A) (dynamic_cast<Ghost*>((A)))
#define GHOST_CHECK(A) (nf(!A, "Special sprite that is supposed to be "\
	"a Ghost sprite is not."))

static void ss_aliases_setup(struct InitData const &d, struct GameData &r) {
	register size_t i = 0;
	std::vector<GameSprite*>::const_iterator ite;
	for (ite = r.sss.begin(); ite != r.sss.end(); ite++)
		switch (i++) {
			case 0 : // pacman
				r.pacman = r.sss[0];
				break;
			case 1 : // stalker
				nf(!r.sss[1], "Null special sprite");
				r.ghost.stalker = CAST_GHOST(r.sss[1]);
				GHOST_CHECK(r.ghost.stalker);
				break;
			case 2 : // kieken
				nf(!r.sss[2], "Null special sprite");
				r.ghost.kieken = CAST_GHOST(r.sss[2]);
				GHOST_CHECK(r.ghost.kieken);
				break;
			case 3 : // random
				nf(!r.sss[3], "Null special sprite");
				r.ghost.random = CAST_GHOST(r.sss[3]);
				GHOST_CHECK(r.ghost.random);
				break;
			case 4 : // retard
				nf(!r.sss[4], "Null special sprite");
				r.ghost.retard = CAST_GHOST(r.sss[4]);
				GHOST_CHECK(r.ghost.retard);
				break;
			default :
				nf(-1, "Unknown special sprite");
		} // switch i
} // ss_aliases_setup
#undef GHOST_CHECK
#undef CAST_GHOST

static void ai_setup(struct InitData const &d, struct GameData &r) {
	// Set up ghost targets
	Targets *targets = new Targets;
	targets->pacman = r.pacman;
	targets->lair = r.animdata->wayhold->getWaypoint(
	 d.weeds[d.TM]);
	// Actor/ActorMovement pairs are already set up

	// Let AI know about those things
	AI::SetTargets(targets);
	AI::SetMoves(r.akmovs);
} // ai_setup

static void collision_setup(InitData const &d, GameData &r) {
	// Each obstacle platform must be registered with all
	// special sprites.
	ObstaclePlatformHolder::obstplats_map& obstplats =
	 r.animdata->plathold->getObstaclePlatforms();
	std::for_each(obstplats.begin(), obstplats.end(),
	 SSS_CollisionRegisterer(d, r));

	// Register all ghosts for collision checking with all waypoints
	std::for_each(r.sss.begin() + 1, r.sss.end(), GWCR(d, r));

	// Set up pacman collision checking with teleporters
	d.cc->Register(
	 r.animdata->wayhold->getWaypoint(d.weeds[d.RT]), // Right teleport
	 r.pacman);
	d.cc->Register(
	 r.animdata->wayhold->getWaypoint(d.weeds[d.LT]), // Left teleport
	 r.pacman);
	// Set up pacman collision checking with eatable bullets & power ups
	std::list<Sprite*> const &sprites = r.animdata->spritehold->
	 getSprites();
	std::for_each(sprites.begin(), sprites.end(), PDCR(d, r));


	// Set up custom callback 
	std::list<ObstacleSprite*> const &obsts = r.animdata->spritehold->
	 getObstacleSprites();
	std::for_each(obsts.begin(), obsts.end(),
	 CocaSetter(d.callbacks->get_coca(), d.callbacks->get_cocaclo()));
} // collision_setup

// Special SpriteS Collision Registerer
void SSS_CollisionRegisterer::operator() (std::pair<obstplatid_t const,
 ObstaclePlatform*>& p)
{
	std::for_each(r.sss.begin(),
	 //r.sss.end(),
	 r.sss.begin() + 1,
	 SOPCR(p.second)
	);
} // SSS_CollisionRegisterer::()

// Sprite - Obstalce Platform Collision Registerer
void SOPCR::operator() (GameSprite* g) {
	o->SetCollisionCheck(g, true);
} // SOPRC::()

// Ghost - Waypoint Collision Registerer
void GWCR::operator() (GameSprite *ghost) {
	std::list<Waypoint*>::iterator ite;
	for (ite = waypoints.begin(); ite != waypoints.end(); ite++)
		d.cc->Register(*ite, ghost);
} // GWCR::()

// Pacman - Dot Collision Registerer
void PDCR::operator() (Sprite *s) {
	// check if sprite is a power up
	std::list<spriteid_t>::const_iterator power_result =
	 std::find_if(d.pids.begin(), d.pids.end(),
	 std::bind1st(std::equal_to<spriteid_t>(), s->getID()));
	// if sprite is a dot sprite
	if (s->getID() >= DOT_SPRITE_ID_FIRST &&
	 s->getID() < DOT_SPRITE_ID_LAST
	) {
		// register it with pacman for collision checking
		// (sprite aliases in GameData have been set at this point)
		d.cc->Register(s, r.pacman);

		// Also, give callback feedback to dot
		s->SetCollisionCallback(Dot::collisionCallback, koka);
	} else if ((power_result != d.pids.end())) { // sprite is a powerup
		// register for collision with pacman
		// (sprite aliases are set)
		d.cc->Register(s, r.pacman);

		// Set special power up callbacl
		s->SetCollisionCallback(powerup_coca, pkoka);
	}
} // PDCR::()

// CocaSetter : CollisionCallback setter
void CocaSetter::operator() (ObstacleSprite *o) {
	o->SetCollisionCallback(coca, &cocaclo);
} // CocaSetter::()

static void teleportals_setup(struct InitData const &d, struct GameData &r){
	Waypoint *portals[] = {
		r.animdata->wayhold->getWaypoint(d.weeds[d.LT]),
		r.animdata->wayhold->getWaypoint(d.weeds[d.RT])
	};

	portals[0]->SetCollisionCallback(
	 Waypoint::TeleportCallback,
	 portals[1]);
	portals[1]->SetCollisionCallback(
	 Waypoint::TeleportCallback,
	 portals[0]);
} // teleportals_setup

// Post setup ----------------------------------------------
void post_setup(PostInitData &pd, InitData &d, GameData &gd) {
	// Start all animations
	start_animations(gd.animdata->animhold, pd.matcher, d.startingTime,
	 DotAnimatorCallback);
	// Update sprite - actor movement map
	d.callbacks->get_cocaclo().akmovs = &gd.akmovs;
} // post_setup

// ----------------- Trivial constructors ------------------
GameData::GameData(void) :
	screen(static_cast<SDL_Surface*>(0)),
	animdata(static_cast<AnimationData*>(0)),
	sss(),
	pacman(static_cast<GameSprite*>(0)),
	ghost(),
	akmovs() { }
AnimationIDs::AnimationIDs(void) :
	mv(4),
	fr(4) { }
InitData::InitData(void) :
	animsetup(static_cast<SetupData*>(0)),
	startingTime(0),
	speeds(),
	anids(), 
	callbacks(CAST(Callbacks*, 0)),
	weeds(3),
	sdlflags(0),
	custset(),
	screen(),
	cc(static_cast<CollisionChecker*>(0)),
	bg(),
	pids() { }
Ghosts::Ghosts(Ghost *d) :
	stalker(d),
	kieken(d),
	random(d),
	retard(d) { }
Screen::Screen(int w, int h, int b, uint32_t f) :
	width(w),
	height(h),
	bpp(b),
	flags(f) { }
template <class arg_t> 
for_each_functor<arg_t>::for_each_functor(InitData const&_d, GameData&_r) :
	d(_d),
	r(_r) { }
SSAMS::SSAMS(struct InitData const&d, struct GameData&r) :
	for_each_functor<GameSprite*>(d, r),
	anids(d.anids.begin()) { }
MovingAnimationFetcher::MovingAnimationFetcher(
 InitData const &d, GameData &r, std::list<MovingAnimation*>& _mv) :
 	for_each_functor<const animid_t&>(d, r),
	mv(_mv) { }
FrameRangeAnimationFetcher::FrameRangeAnimationFetcher(
 InitData const &d, GameData &r, std::list<FrameRangeAnimation*>& _fr) :
 	for_each_functor<const animid_t&>(d, r),
	fr(_fr) { }
AnimatorSetup::AnimatorSetup(InitData const &d, GameData &r, GameSprite *_g,
 std::vector<MovingAnimator*> &_mvtors,
 std::vector<FrameRangeAnimator*> &_frtors) :
 	for_each_functor<Animation*>(d, r),
	g(_g),
	mvtors(_mvtors),
	frtors(_frtors) { }
SSS_CollisionRegisterer::SSS_CollisionRegisterer(InitData const &_d,
 GameData &_r) :
 	for_each_functor<std::pair<obstplatid_t const, ObstaclePlatform*>&>
	(_d, _r) { }
SOPCR::SOPCR(ObstaclePlatform *_o) :
	o(_o) { }
GWCR::GWCR(InitData const &d, GameData &r) :
	for_each_functor<GameSprite*>(d, r),
	waypoints(r.animdata->wayhold->getWaypoints()) { }
CocaSetter::CocaSetter(Sprite::CollisionCallback _coca, _cocaclo &cocaclo_):
	coca(_coca),
	cocaclo(cocaclo_) { }
PDCR::PDCR(InitData const &d, GameData &r) :
	for_each_functor<Sprite*>(d, r),
	koka(new Dot::_coca()),
	pkoka(new _pcoca())
{
	koka->cc = pkoka->cc = d.cc;
	koka->pacman = r.pacman;
	pkoka->sss = &r.sss;
	pkoka->ghost = &r.ghost;
	pkoka->filmhold = r.animdata->filmhold;
} // PDCR::PDCR

// ----------------- Even more trivial destructors ------------------
Ghosts::~Ghosts(void) { }
template <class arg_t>
for_each_functor<arg_t>::~for_each_functor(void) { }
AnimationIDs::~AnimationIDs(void) { }
InitData::~InitData(void) { }
Screen::~Screen(void) { }
