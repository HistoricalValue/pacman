#include "sakutest.hpp"
#include "SurfaceLoader.hpp"

namespace sakutest{
using namespace cs454_2006;
void setup(data& d) {
	// Init libs
	db("Initialise SDL");
	nf(SDL_Init(SDL_INIT_VIDEO/*|SDL_INIT_AUDIO*/), "SDL Init");
	d.screen = SDL_SetVideoMode(
	 SCREEN_WIDTH,
	 SCREEN_HEIGHT,
	 SCREEN_BPP,
	 SCREEN_FLAGS
	);
	db("Initialise TTF");
	nf(TTF_Init(), "TTF Init");

	// Init paths
	d.animation_film_config_file_path = new std::string(
	 ANIMATION_FILM_CONFIG_FILE);
	d.animation_holder_config_file_path = new std::string(
	 ANIMATION_HOLDER_CONFIG_FILE);
	d.sprite_config_file_path = new std::string(
	 SPRITE_CONFIG_FILE);
	d.animation_setup_config_file_path = new std::string(
	 ANIMATION_SETUP_CONFIG_FILE);
	d.obstacle_platform_config_file_path = new std::string(
	 OBSTACLE_PLATFORM_CONFIG_FILE);
	d.waypoints_config_file_path = new std::string(
	 WAYPOINTS_CONFIG_FILE);

	// Timestamp
	d.startingTime = cs454_2006::getTimestamp();

	// create animations 
	SetupData setup_d = {
		d.animation_film_config_file_path,
		d.animation_holder_config_file_path,
		d.sprite_config_file_path,
		d.obstacle_platform_config_file_path,
		d.waypoints_config_file_path
	};
	d.animation_data = setup_animations(&setup_d);
	// Set bug bitmap for junction visualisation
	d.animation_data->wayhold->setBug(SurfaceLoader::getInstance()->
	 loadSurface(*new std::string("./resources/animation_films/"
	 "waypoint.png")));

	// Fetch custom sprites
	d.pacman = dynamic_cast<GameSprite*>(
	 d.animation_data->spritehold->getSprite(1001));
	nf(!d.pacman, "Sprite 1001 must be pacman");
	
	// After move call
	d.amc = new after_move_call;

	// Custom animators
	d.animators = new __animators;
	d.animations = new __animations;
	d.yums = new __yums;
	d.yams = new __yams;
	//
	d.animators->pac = new MovingAnimator(false);
	d.animators->box = new MovingAnimator(false);
	d.animators->up = new MovingAnimator(false);
	d.animators->right = new MovingAnimator(false);
	d.animators->down = new MovingAnimator(false);
	d.animators->left = new MovingAnimator(false);
	d.animators->snaily[0] = new MovingAnimator(false);
	d.animators->snaily[1] = new MovingAnimator(false);
	d.animators->snaily[2] = new MovingAnimator(false);
	d.animators->snaily[3] = new MovingAnimator(false);
	d.animators->pinky[0] = new MovingAnimator(false);
	d.animators->pinky[1] = new MovingAnimator(false);
	d.animators->pinky[2] = new MovingAnimator(false);
	d.animators->pinky[3] = new MovingAnimator(false);
	//
	d.yums->u = new FrameRangeAnimator(false);
	d.yums->r = new FrameRangeAnimator(false);
	d.yums->d = new FrameRangeAnimator(false);
	d.yums->l = new FrameRangeAnimator(false);
	d.yums->snaily[0] = new FrameRangeAnimator(false);
	d.yums->snaily[1] = new FrameRangeAnimator(false);
	d.yums->snaily[2] = new FrameRangeAnimator(false);
	d.yums->snaily[3] = new FrameRangeAnimator(false);
	d.yums->pinky[0] = new FrameRangeAnimator(false);
	d.yums->pinky[1] = new FrameRangeAnimator(false);
	d.yums->pinky[2] = new FrameRangeAnimator(false);
	d.yums->pinky[3] = new FrameRangeAnimator(false);

	//
	// remove animators that must from holder
	AnimatorHolder::Cancel(d.animators->up);
	AnimatorHolder::Cancel(d.animators->right);
	AnimatorHolder::Cancel(d.animators->down);
	AnimatorHolder::Cancel(d.animators->left);
	//
	AnimatorHolder::Cancel(d.yums->u);
	AnimatorHolder::Cancel(d.yums->r);
	AnimatorHolder::Cancel(d.yums->l);
	AnimatorHolder::Cancel(d.yums->d);

	// custom animations
	//
	// Moving
	d.animations->up = d.animation_data->animhold->
	 getMovingAnimation(1002);
	d.animations->right = d.animation_data->animhold->
	 getMovingAnimation(1003);
	d.animations->down = d.animation_data->animhold->
	 getMovingAnimation(1004);
	d.animations->left = d.animation_data->animhold->
	 getMovingAnimation(1005);
	for (int i = 0; i < 4; i++){
		d.animations->snaily[i] = d.animation_data->animhold->
		 getMovingAnimation(3000 + i);
		d.animations->pinky[i] = d.animation_data->animhold->
		 getMovingAnimation(3010 + i);
	}
	// Frame range (yums)
	d.yams->u =d.animation_data->animhold->getFrameRangeAnimation(2005);
	d.yams->r =d.animation_data->animhold->getFrameRangeAnimation(2004);
	d.yams->l =d.animation_data->animhold->getFrameRangeAnimation(2003);
	d.yams->d =d.animation_data->animhold->getFrameRangeAnimation(2002);
	for (int i = 0; i < 4; i++){
		d.yams->snaily[i] = d.animation_data->animhold->
		 getFrameRangeAnimation(3004 + i);
		d.yams->pinky[i] = d.animation_data->animhold->
		 getFrameRangeAnimation(3014 + i);
	}
	// Start animators
	d.animators->up->Start(d.pacman, d.animations->up, d.startingTime);
	d.animators->right->Start(d.pacman, d.animations->right, d.startingTime);
	d.animators->down->Start(d.pacman, d.animations->down, d.startingTime);
	d.animators->left->Start(d.pacman, d.animations->left, d.startingTime);
	d.yums->u->Start(d.pacman, d.yams->u, d.startingTime);
	d.yums->r->Start(d.pacman, d.yams->r, d.startingTime);
	d.yums->d->Start(d.pacman, d.yams->d, d.startingTime);
	d.yums->l->Start(d.pacman, d.yams->l, d.startingTime);
	//
	// For little snaily too
	for (int i = 0; i < 4; i++) { 
		Sprite *snail, *pink;
		d.animators->snaily[i]->Start(snail = d.animation_data->
		 spritehold->getSprite(3003),
		 d.animations->snaily[i], d.startingTime);
		d.yums->snaily[i]->Start(snail, d.yams->snaily[i],
		 d.startingTime);
		d.animators->pinky[i]->Start(pink = d.animation_data->
		 spritehold->getSprite(3004),
		 d.animations->pinky[i], d.startingTime);
		d.yums->pinky[i]->Start(pink, d.yams->pinky[i],
		 d.startingTime);
	}

	// create actor movement objects
	//
	// For pacman
	std::vector<MovingAnimator*> pacmovs;
	pacmovs.push_back(d.animators->up);
	pacmovs.push_back(d.animators->right);
	pacmovs.push_back(d.animators->down);
	pacmovs.push_back(d.animators->left);
	std::vector<FrameRangeAnimator*> yummovs;
	yummovs.push_back(d.yums->u);
	yummovs.push_back(d.yums->r);
	yummovs.push_back(d.yums->d);
	yummovs.push_back(d.yums->l);
	d.pacmov = new ActorMovement(d.pacman, pacmovs, yummovs, *d.amc,
	 d.startingTime);
	// For snaily
	std::vector<MovingAnimator*> snailymovs, pinkymovs;
	std::vector<FrameRangeAnimator*> snailyyummovs, pinkyyummovs;
	for (int i = 0; i < 4; i++) {
		snailymovs.push_back(d.animators->snaily[i]);
		snailyyummovs.push_back(d.yums->snaily[i]);
		pinkymovs.push_back(d.animators->pinky[i]);
		pinkyyummovs.push_back(d.yums->pinky[i]);
	}
	d.snailymov = new ActorMovement(dynamic_cast<Ghost*>(
	 d.animation_data->spritehold->
	 getSprite(3003)), snailymovs, snailyyummovs, *d.amc,
	 d.startingTime);
	d.pinkymov = new ActorMovement(dynamic_cast<Ghost*>(
	 d.animation_data->spritehold->
	 getSprite(3004)), pinkymovs, pinkyyummovs, *d.amc,
	 d.startingTime);
	
	// Set up AI
	Targets *targets = new Targets;
	targets->pacman = d.pacman;
	targets->lair = d.animation_data->wayhold->getWaypoint(802);
	AI::SetTargets(targets);
	std::map<GameSprite*, ActorMovement*> actormoves;
	actormoves[d.pacman] = d.pacmov;
	actormoves[dynamic_cast<GameSprite*>(
	 d.animation_data->spritehold->getSprite(3003))] = d.snailymov;
	actormoves[dynamic_cast<GameSprite*>(
	 d.animation_data->spritehold->getSprite(3004))] = d.pinkymov;
	AI::SetMoves(actormoves);

	// register the above for collision checking
	setUpCollisions(d);

	// create the matcher for animtion starting
	d.matcher = new Matcher(d.animation_data->spritehold);
	start_animations(
	 d.animation_data->animhold,
	 d.matcher,
	 getTimestamp()
	);

	// create background colour for redrawing
	create_bgcolor(d);

	// set after move call
	AnimatorHolder::setAfterMoveCall(d.amc);

	// For handling input events
	//SDL_EnableKeyRepeat(10, 10);

	// Set up teleportation waypoints
	Waypoint* teleportals[] = {
		d.animation_data->wayhold->getWaypoint(666),
		d.animation_data->wayhold->getWaypoint(667)
	};
	for (int i = 0; i < 2; i++)
		teleportals[i]->SetCollisionCallback(
		 Waypoint::TeleportCallback,
		 teleportals[i == 0? 1 : 0]
		);

	// Set up targets for AI
}
} // namespace sakutest

namespace cs454_2006 {
struct RegisterCollision :
 public std::binary_function<Sprite*, Sprite*, void>
{
	void operator() (Sprite* actor, Sprite* self) const;
};
struct setCustomCollisionCallback : public std::unary_function<Sprite*,void>
{
	void operator () (Sprite* obstacle);
	setCustomCollisionCallback(Sprite::CollisionCallback, void* c =
	 static_cast<void*>(0));
	private :
	Sprite::CollisionCallback cc;
	void *closure;
};
} // namespace cs45_2005

namespace sakutest {
void setUpCollisions(data& d) {
	SpriteHolder* sh;
	std::list<ObstacleSprite*> const& obstsps =
	 (sh = d.animation_data->spritehold)->getObstacleSprites();
	GameSprite *pacman, *box = NULL;
	ObstaclePlatformHolder::obstplats_map& plats =
	 d.animation_data->plathold->getObstaclePlatforms();

	nf(!(
	 ( pacman = dynamic_cast<GameSprite*>(sh->getSprite(1001)) ) &&
	 ( box    = dynamic_cast<GameSprite*>(sh->getSprite(1002)) ) ),
	 "Not a game sprite"
	);

	// Obstacles are registered by Platforms
	// ===
	// for each obstacle, add collision with those two
//	std::for_each(obstsps.begin(), obstsps.end(),
//	 std::bind1st(RegisterCollision(), pacman) );
//	std::for_each(obstsps.begin(), obstsps.end(),
//	 std::bind1st(RegisterCollision(), box) );

	// Ghost snail id-s
	std::list<int> ghostids;
	ghostids.push_back(3003);
	// Instead, register each pushable sprite with all platforms
	ObstaclePlatformHolder::obstplats_map::iterator ite;
	for (ite = plats.begin(); ite != plats.end(); ite++) {
		ite->second->SetCollisionCheck(pacman, true);
		ite->second->SetCollisionCheck(box, true);
		// for each ghost snail, register collision
		std::list<int>::const_iterator gite;
		for (gite = ghostids.begin();gite != ghostids.end();gite++){
			Ghost* g = dynamic_cast<Ghost*>(sh->getSprite(
			 *gite));
			nf(!g, "Sprite with 3003 <= id < 4000 is no a "
			 "ghost game sprite.");
			ite->second->SetCollisionCheck(g, true);
		}
	}

	// set up waypoint collisions with ghosts
	// TODO add all ghosts after testing is done
	Ghost* a_ghost = dynamic_cast<Ghost*>(sh->getSprite(3003));
	Ghost* pinky = dynamic_cast<Ghost*>(sh->getSprite(3004));
	nf(!a_ghost || !pinky, "Sprite with 3003 <= id < 4000 is no a "
	 "ghost game sprite.");
	std::list<Waypoint*> wps = 
	 d.animation_data->wayhold->getWaypoints();
	std::list<Waypoint*>::iterator wite;
	for (wite = wps.begin(); wite != wps.end(); wite++) {
		CollisionChecker::Singleton()->Register(*wite, a_ghost);
		CollisionChecker::Singleton()->Register(*wite, pinky);
	}

	// Set up pacman collision with two teleporters
	Waypoint* teleportals[] = {
		d.animation_data->wayhold->getWaypoint(666),
		d.animation_data->wayhold->getWaypoint(667)
	};
	for (int i =  0; i < 2; i++)
		CollisionChecker::Singleton()->Register(teleportals[i],
		 d.pacman);

	// set custom callback
	std::for_each(obstsps.begin(), obstsps.end(),
	 setCustomCollisionCallback(collision_callback, &d) );
}
} // namespace sakutest
void cs454_2006::RegisterCollision::operator () (Sprite* actor,
 Sprite* self) const 
{
	CollisionChecker::Singleton()->Register(self, actor);
}

void cs454_2006::setCustomCollisionCallback::operator() (Sprite* obstacle) {
	obstacle->SetCollisionCallback(cc, closure);
}

cs454_2006::setCustomCollisionCallback::setCustomCollisionCallback(
 Sprite::CollisionCallback _cc, void* _closure) :
 cc(_cc), closure(_closure) { }
