#include "sakutest.hpp"

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

	// Timestamp
	d.startingTime = cs454_2006::getTimestamp();

	// create animations 
	SetupData setup_d = {
		d.animation_film_config_file_path,
		d.animation_holder_config_file_path,
		d.sprite_config_file_path
	};
	d.animation_data = setup_animations(&setup_d);

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
	//
	d.yums->u = new FrameRangeAnimator(false);
	d.yums->r = new FrameRangeAnimator(false);
	d.yums->d = new FrameRangeAnimator(false);
	d.yums->l = new FrameRangeAnimator(false);
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
	// Frame range (yums)
	d.yams->u =d.animation_data->animhold->getFrameRangeAnimation(2005);
	d.yams->r =d.animation_data->animhold->getFrameRangeAnimation(2004);
	d.yams->l =d.animation_data->animhold->getFrameRangeAnimation(2003);
	d.yams->d =d.animation_data->animhold->getFrameRangeAnimation(2002);

	// Start animators
	d.animators->up->Start(d.pacman, d.animations->up, d.startingTime);
	d.animators->right->Start(d.pacman, d.animations->right, d.startingTime);
	d.animators->down->Start(d.pacman, d.animations->down, d.startingTime);
	d.animators->left->Start(d.pacman, d.animations->left, d.startingTime);
	d.yums->u->Start(d.pacman, d.yams->u, d.startingTime);
	d.yums->r->Start(d.pacman, d.yams->r, d.startingTime);
	d.yums->d->Start(d.pacman, d.yams->d, d.startingTime);
	d.yums->l->Start(d.pacman, d.yams->l, d.startingTime);

	// create actor movement objects
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

	nf(!(
	 ( pacman = dynamic_cast<GameSprite*>(sh->getSprite(1001)) ) &&
	 ( box    = dynamic_cast<GameSprite*>(sh->getSprite(1002)) ) ),
	 "Not a game sprite"
	);

	// for each obstacle, add collision with those two
	std::for_each(obstsps.begin(), obstsps.end(),
	 std::bind1st(RegisterCollision(), pacman) );
	std::for_each(obstsps.begin(), obstsps.end(),
	 std::bind1st(RegisterCollision(), box) );

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
