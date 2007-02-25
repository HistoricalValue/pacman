/* Power up sprite callbacks and related stuff.
 */

#ifndef __PowerUp_hpp__
#define __PowerUp_hpp__

#include "CollisionChecker.hpp"
#include "GameSprite.hpp"
#include "ActorMovement.hpp"
#include "AnimationFilmHolder.hpp"
#include "AnimationHolder.hpp"
#include "Scheduler.hpp"
#include "Waypoint.hpp"
#include <map>

struct _pcoca { // Power up collision callback data
	CollisionChecker *cc;
	std::map<GameSprite*, ActorMovement*> *akmovs;
	struct Ghosts *ghost;
	AnimationFilmHolder *filmhold;
	AnimationHolder *animhold;
	Scheduler *sch;
}; // struct _pcoca
extern void powerup_coca(Sprite*, Sprite*, void *c = CAST(void*, 0));

struct _gcoca : public _pcoca {
	Waypoint *left_right, *down;
}; // struct _gcoca
// Pacman-Ghost collision callback
extern void Ghost_collision_callback(Sprite *, Sprite *,
 void *c = CAST(void*, 0));

extern void ghost_uneating_callback(Sprite*, Sprite*,
 void *c = CAST(void*, 0));
#endif // __PowerUp_hpp__
