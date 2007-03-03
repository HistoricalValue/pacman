/* Callbacks related to ghosts.
 */

#ifndef __ghost_hpp__
#define __ghost_hpp__

#include "PowerUp.hpp"

struct _gcoca : public _pcoca {
	Waypoint *left_right, *down, *lair;
}; // struct _gcoca

// Pacman-Ghost collision callback
extern void Ghost_collision_callback(Sprite *, Sprite *,
 void *c = CAST(void*, 0));

// Callback which happens when a ghost is found back into the lair.
// It sets the eatten ghost back to its normal state.
extern void ghost_uneating_callback(Sprite*, Sprite*,
 void *c = CAST(void*, 0));
#endif // __ghost_hpp__
