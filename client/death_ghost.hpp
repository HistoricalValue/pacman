/* Death - ghost
 *
 * The death of pacman caused by collision with the Ghosts.
 */

#ifndef __death_ghost_hpp__
#define __death_ghost_hpp__

#include "commons.hpp"
#include "Ghost.hpp"
#include "ghost.hpp"

// The callback called in the case of Ghost - pacman collision
extern 
void ghost_death_callback(Ghost *, GameSprite *, _gcoca *);
#endif // __death_ghost_hpp__
