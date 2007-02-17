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

enum ss_t { // special sprite type
	ss_pacman, ss_stalker, ss_kieken, ss_random, ss_retard
}; // enum ss_t
struct Ghosts {
	Ghost *stalker, *kieken, *random, *retard;

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
	 int width = 496,
	 int height = 600,
	 int bpp = 32,
	 uint32_t flags = SDL_HWSURFACE|SDL_DOUBLEBUF);
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
		LT = 0, // left teleport
		RT = 1, // right teleport
		TM = 2  // traffic man
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

	// Ignore
	InitData(void); ~InitData(void);
}; // class InitData

struct GameData *setup(struct InitData *);
struct GameData &setup(struct InitData &);

struct PostInitData {
	// Animation to Sprite matcher
	Anim2SpriteMatcher *matcher;
}; // struct PostInitData

void post_setup(PostInitData &, InitData &, GameData &);
#endif // __client_hpp__
