/* Configuration definitions.
 *
 * Only defines please : ) Have a nice day.
 */

#ifndef __config_h__
#define __config_h__

#include "SDL/SDL.h"

/* Most of the following are self descriptive */
#define ANIMATION_FILM_CONFIG_FILE \
	"./resources/config/animationfilms.config"
#define ANIMATION_CONFIG_FILE \
	"./resources/config/animations.config"
#define SPRITE_CONFIG_FILE \
	"./resources/config/sprites.config"
#define ANIMATION_SETUP_CONFIG_FILE \
	"./resources/config/animation_setup.config"
#define OBSTACLE_PLATFORM_CONFIG_FILE \
	"./resources/config/obstacle_platforms.config"
#define WAYPOINTS_CONFIG_FILE \
	"./resources/config/junctions.config"

#define SCREEN_WIDTH 	(496)
#define SCREEN_HEIGHT 	(600)
#define SCREEN_BPP	(32)
#define SCREEN_FLAGS	(SDL_HWSURFACE|SDL_DOUBLEBUF)

/* Special sprite types */
/* Dots */
#define DOT_SPRITE_ID_FIRST	2000
#define DOT_SPRITE_ID_LAST	3000
/* Ghosts */
#define GHOST_SPRITE_ID_FIRST	3003
#define GHOST_SPRITE_ID_LAST	4000
#endif /* __config_h__ */
