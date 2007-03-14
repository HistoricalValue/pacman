/* Callbacks related to ghosts.
 */

#ifndef __ghost_hpp__
#define __ghost_hpp__

#include "PowerUp.hpp"
#include "inputControl.hpp"

struct _gcoca : public _pcoca {
	Waypoint *left_right, *down, *lair;
	std::map<GameSprite*, SDL_Rect> *initpos;
	bool *theatre_mode;
	GameData::io_bools *bools;
}; // struct _gcoca

// Pacman-Ghost collision callback
extern void Ghost_collision_callback(Sprite *, Sprite *,
 void *c = CAST(void*, 0));

// Callback which happens when a ghost is found back into the lair.
// It sets the eatten ghost back to its normal state.
extern void ghost_uneating_callback(Sprite*, Sprite*,
 void *c = CAST(void*, 0));

_gcoca *getacoca(InitData &, GameData &);

#endif // __ghost_hpp__
