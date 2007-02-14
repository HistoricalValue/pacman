#include "client.hpp"
#include "support.hpp"
#include "config.h"
int main_pac(int argc, char *argv[]) {
	// Clean exit first
	atexit(cleanup);
	
	InitData d;
	// Assign values to initialisation data
	//
	// Config files
	d.animsetup = new SetupData;
	d.animsetup->animation_films = new std::string(
	 ANIMATION_FILM_CONFIG_FILE);
	d.animsetup->animations = new std::string(
	 ANIMATION_CONFIG_FILE);
	d.animsetup->sprites = new std::string(
	 SPRITE_CONFIG_FILE);
	d.animsetup->obstacle_platform = new std::string(
	 OBSTACLE_PLATFORM_CONFIG_FILE);
	d.animsetup->waypoints = new std::string(
	 WAYPOINTS_CONFIG_FILE);
	//
	// Special sprites IDs
	d.speeds.assign(2, 0);
	d.speeds[ss_pacman] = 1001;
	d.speeds[ss_stalker] = 3003;
	//
	// Animation IDs for each special sprite
	d.anids.assign(2, *new AnimationIDs);
	for (size_t i = 0; i < 4; i++) {
		// Pacman
		d.anids[ss_pacman].mv[i] = (1002 + i);
		d.anids[ss_pacman].fr[i] = (2002 + i);
		// Stalker
		d.anids[ss_stalker].mv[i] = (3000 + i);
		d.anids[ss_stalker].fr[i] = (3004 + i);
	}
	//
	// Create after move callback
	// TODO change singleton policy
	d.amc = new Callbacks::amc(CollisionChecker::Singleton());
	//
	// Starting time
	d.startingTime = getTimestamp();

	setup(d);
	return 0;
}
