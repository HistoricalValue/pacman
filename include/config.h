/* Configuration definitions.
 *
 * Only defines please : ) Have a nice day.
 */

#ifndef __config_h__
#define __config_h__

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

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
/* Obstacles */
#define OBSTACLE_SPRITE_ID_FIRST	0
#define OBSTACLE_SPRITE_ID_LAST		999
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
#define EATABLE_DURATION		10000 // miliseconds
#define MAP_RESET_DELAY			5000 // miliseconds
#define RESTARTING_DELAY		2700 // miliseconds
#define POINTS_WORTH_DOT		5
#define POINTS_WORTH_PUP		20
#define POINTS_WORTH_GHOST		100

/* Layout offset */
#define LAYOUT_X_OFFSET			(0)
#define LAYOUT_Y_OFFSET			(40)

/* Macros */
#define IS_OBSTACLE_SPRITE(A)	(\
		(A) >= OBSTACLE_SPRITE_ID_FIRST		&& \
		(A) <= OBSTACLE_SPRITE_ID_LAST			)
#define IS_DOT_SPRITE(A) 	(\
		(A) >= DOT_SPRITE_ID_FIRST		&& \
		(A) <= DOT_SPRITE_ID_LAST			)



#endif /* __config_h__ */
