/* client.hpp
 *
 * All client side operations and structures.
 */
#ifndef __client_hpp__
#define __client_hpp__
#include <vector>
#include <map>
#include "AnimationSetup.hpp"
#include "Ghost.hpp"
#include "GameSprite.hpp"
#include "ActorMovement.hpp"
#include "Animation.hpp"
#include "SDL/SDL_ttf.h"
#include "support.hpp"
#include "config.h"
#include "Scheduler.hpp"
#include "CustomPostinit_Data.hpp"
#include "GameStats.hpp"

enum ss_t { // special sprite type
	ss_pacman, ss_stalker, ss_kieken, ss_random, ss_retard
}; // enum ss_t
struct Ghosts {
	Ghost *stalker, *kieken, *random, *retard, *player2;

	// Ignore
	Ghosts(Ghost *d = static_cast<Ghost*>(0)); ~Ghosts(void);
}; // struct Ghosts
struct GameData {
	// The screen
	SDL_Surface *screen;
	// Contains most (or all) holders
	// * Animation Film Holder
	// * Animation Holder
	// * Sprite Holder
	// * Obstacle Platform Holder
	// * Waypoint Holder
	AnimationData *animdata;
	// Our special sprites
	std::vector<GameSprite*> sss; // special sprites
	GameSprite *pacman;
	struct Ghosts ghost;
	// And their ActorMovement instances
	std::map<GameSprite*, ActorMovement*> akmovs;
	// Background colour for redrawing
	Uint32 bg;
	// Loop time
	timestamp_t currTime;
	// The collision checker
	CollisionChecker *cc;
	// The task scheduler
	Scheduler *sch;
	// GameStats
	GameStats *stats;
	// Custom setup data
	custompostinit_data *custom;
	// Values for input control to check
	struct io_bools {
		bool exit, paused, theatre_mode, second_player, start,
		 won;
		io_bools(
			  bool exit = false
			, bool paused = false
			, bool theatre_mode = false
			, bool second_player = false
			, bool start = false
			, bool won = false
		);
	} *bools;

	// Ignore
	GameData(void); ~GameData(void);
}; // class GameData

struct AnimationIDs {
	std::vector<animid_t> mv;
	std::vector<animid_t> fr;

	// Ignore
	AnimationIDs(void); ~AnimationIDs(void);
}; // struct AnimationIDs
struct Screen {
	int width, height, bpp;
	uint32_t flags;

	// Ignore
	Screen(
	 int width = SCREEN_WIDTH,
	 int height = SCREEN_HEIGHT,
	 int bpp = SCREEN_BPP,
	 uint32_t flags = SCREEN_FLAGS);
	~Screen(void);
}; // struct Screen
struct InitData {
	// Contains information to fill up animdata.
	SetupData *animsetup;
	// The timestamp with which everything will be initialised
	timestamp_t startingTime;
	// Special sprites IDs.
	// Order must follow the enum ss_t order.
	std::vector<spriteid_t> speeds; // spid
	// Per sprite animation IDs
	std::vector<AnimationIDs> anids;
	// Callbacks: contains
	// * After move callback, for animators
	// * CollisionCallback for obstacle collisions
	struct Callbacks *callbacks;
	// Special waypoint IDs.
	// 0 :: left teleport.
	// 1 :: right teleport.
	// 2 :: ghost lair traffic man
	enum wp_t { // waypoint type
		  LT = 0 // left teleport
		, RT = 1 // right teleport
		, TM = 2 // traffic man - away
		, TI = 3 // traffic man - inside
		, LR = 4 // the lair target
	};
	std::vector<waypointid_t> weeds; // wid
	// Library init flags
	uint32_t sdlflags;
	// Custom setup functions
	typedef void (*setup_func_t)(struct InitData const&,
	 struct GameData &);
	std::list<setup_func_t> custset;
	// Screen initialisation data
	struct Screen screen;
	// Collision Checker
	CollisionChecker *cc;
	// Background colour
	Colour bg;
	// Power up sprites IDs
	std::list<spriteid_t> pids;

	// Ignore
	InitData(void); ~InitData(void);
}; // class InitData

extern void setup(struct InitData *, struct GameData *);
extern void setup(struct InitData &, struct GameData &);

struct PostInitData {
	// Animation to Sprite matcher
	Anim2SpriteMatcher *matcher;
	// Post Init Custom functions
	std::list<void(*)(PostInitData&, InitData&, GameData&)> user;
}; // struct PostInitData

void post_setup(PostInitData &, InitData &, GameData &);

#endif // __client_hpp__
