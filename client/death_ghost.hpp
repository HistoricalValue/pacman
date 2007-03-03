/* Death - ghost
 *
 * The death of pacman caused by collision with the Ghosts.
 */

#ifndef __death_ghost_hpp__
#define __death_ghost_hpp__

#include "Sprite.hpp"
#include "commons.hpp"

// The callback called in the case of Ghost - pacman collision
extern 
void ghost_death_callback(Sprite *, Sprite *, void *c = CAST(void*, 0));
#endif // __death_ghost_hpp__
