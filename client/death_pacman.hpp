/* Death - ghost
 *
 * The death of pacman caused by collision with the Ghosts.
 */

#ifndef __death_ghost_hpp__
#define __death_ghost_hpp__

#include "commons.hpp"
#include "Ghost.hpp"
#include "_ghost.hpp"

// The callback called in the case of Ghost - pacman collision
extern 
void pacman_death_by_ghost_callback(Ghost *, GameSprite *, _gcoca *);

// The callback called when pacman is smashed by a moving obstacle
struct _shca { // Shmash Callback (closure data)
	_gcoca *gkoka; // can't escape this.. it's drugs
	_shca( _gcoca *gkoka );
	~_shca(void);
}; // struct _shca
extern
void pacman_death_by_smash_callback(GameSprite *pacman, Sprite *smasher,
 void *closure);

// Functions to set things in theatre mode and back.
extern void switch_to_theatre_mode(_gcoca *gkoka);
extern void leave_theatre_mode(_gcoca *gkoka);
#endif // __death_ghost_hpp__
