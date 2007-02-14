#include "AnimationFilmHolder.hpp"
#include "AnimationHolder.hpp"
#include "AnimatorHolder.hpp"
#include "FrameRangeAnimation.hpp"
#include "FrameRangeAnimator.hpp"
#include "MovingAnimator.hpp"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SpriteHolder.hpp"
#include "commons.hpp"
#include <string>
#include <sys/time.h>
#include <time.h>
#include "AnimationSetup.hpp"
#include "Animator.hpp"
#include "CollisionChecker.hpp"
#include "ActorMovement.hpp"
#include "Ghost.hpp"
#include "AI.hpp"

#define ANIMATION_FILM_CONFIG_FILE 	"./resources/config/animationfilms.config"
#define ANIMATION_HOLDER_CONFIG_FILE	"./resources/config/animations.config"
#define SPRITE_CONFIG_FILE		"./resources/config/sprites.config"
#define ANIMATION_SETUP_CONFIG_FILE	"./resources/config/animation_setup.config"
#define OBSTACLE_PLATFORM_CONFIG_FILE	"./resources/config/obstacle_platforms.config"
#define WAYPOINTS_CONFIG_FILE		"./resources/config/junctions.config"
#define SCREEN_WIDTH 	(496)
#define SCREEN_HEIGHT 	(600)
#define SCREEN_BPP	(32)
#define SCREEN_FLAGS	(SDL_HWSURFACE|SDL_DOUBLEBUF)

namespace sakutest{
struct __animators { MovingAnimator *up, *right, *down, *left, *pac, *box,
 *snaily[4], *pinky[4];};
struct __animations { MovingAnimation *up, *right, *down, *left,
 *snaily[4], *pinky[4]; };
struct __yums {FrameRangeAnimator *u, *r, *d, *l, *snaily[4], *pinky[4];};
struct __yams {FrameRangeAnimation *u, *r, *d, *l, *snaily[4], *pinky[4];};


enum move_t { NOMOVE = 0, UP = 1, RIGHT = 2, DOWN = 3, LEFT = 4};
struct data {
	SDL_Surface* screen;
	Uint32* bgcolor;
	std::string
	 *animation_film_config_file_path,
	 *animation_holder_config_file_path,
	 *sprite_config_file_path,
	 *animation_setup_config_file_path,
	 *obstacle_platform_config_file_path,
	 *waypoints_config_file_path;
	timestamp_t startingTime, currTime;
	AnimationData* animation_data;
	__animators* animators;
	__animations* animations;
	GameSprite* pacman, *box;
	Sprite::CollisionCallback colcal;
	Anim2SpriteMatcher* matcher;
	move_t moves[2];
	ActorMovement* pacmov, *snailymov, *pinkymov;
	__yums* yums;
	__yams* yams;
	amc_t* amc;
};
struct Matcher : public Anim2SpriteMatcher {
	Sprite* operator() (Animation*) const;
	Matcher(SpriteHolder*);
	~Matcher(void);
};

extern data d;

void setup(data&);
void cleanup(void);
void setUpCollisions(data&);
void create_bgcolor(data&);
void handleEvent(data&, SDL_Event&);
void handleEvent_keyDown(data&, SDL_Event&);
void handleEvent_keyUp(data&, SDL_Event&);
void collision_callback(Sprite*,Sprite*,void*c=static_cast<void*>(0));

struct after_move_call : amc_t { 
	int operator() (Animator*) const;
	after_move_call(void);
	private :
	CollisionChecker* cc;
};
} //namespace sakutest
