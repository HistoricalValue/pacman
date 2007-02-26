/* Configuration definitions.
 *
 * Only defines please : ) Have a nice day.
 */

#ifndef __config_h__
#define __config_h__

#include "SDL/SDL_mixer.h"
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

#define SCREEN_WIDTH 	(800)
#define SCREEN_HEIGHT 	(600)
#define SCREEN_BPP	(32)
#define SCREEN_FLAGS	(SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_INIT_AUDIO)
/* Special sprite IDs */
#define PACMAN		1001
#define STALKER
#define KIEKEN
#define RANDOM
#define RETARD

/* Special sprite types */
/* Dots */
#define DOT_SPRITE_ID_FIRST	2000
#define DOT_SPRITE_ID_LAST	3000
/* Ghosts */
#define GHOST_SPRITE_ID_FIRST	3003
#define GHOST_SPRITE_ID_LAST	4000
/* Waypoints */
#define WAYPOINT_LAIR			802
#define WAYPOINT_TRAFICMAN_LEFTRIGHT	800
#define WAYPOINT_TRAFICMAN_AWAY		WAYPOINT_TRAFICMAN_LEFTRIGHT
#define WAYPOINT_GET_BACK		WAYPOINT_TRAFICMAN_AWAY
#define WAYPOINT_TRAFICMAN_INSIDE	888
#define WAYPOINT_UNEATER		850

/* Settings */
#define EATABLE_DURATION		10000 // milisecond
#endif /* __config_h__ */
