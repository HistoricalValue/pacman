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
#include "GameStats.hpp"
#include <map>

struct _pcoca { // Power up collision callback data
	CollisionChecker *cc;
	std::map<GameSprite*, ActorMovement*> *akmovs;
	struct Ghosts *ghost;
	AnimationFilmHolder *filmhold;
	AnimationHolder *animhold;
	Scheduler *sch;
        GameStats *gs;
}; // struct _pcoca
extern void powerup_coca(Sprite*, Sprite*, void *c = CAST(void*, 0));
#endif // __PowerUp_hpp__
