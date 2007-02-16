#include "client.hpp"
#include "support.hpp"
#include "config.h"

static void setup_setup_data(InitData &);
static void setup_post_setup_data(PostInitData &, GameData &);

int main_pac(int argc, char *argv[]) {
	// Clean exit first
	atexit(cleanup);
	
	InitData d;
	setup_setup_data(d);
	GameData &gd = setup(d);

	PostInitData pd;
	setup_post_setup_data(pd, gd);
	post_setup(pd, d, gd);
	return 0;
}

static void setup_setup_data(InitData &d) {
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
	// Point to collision checker
	// TODO change singleton policy
	d.cc = CollisionChecker::Singleton();
	// Create callbacks
	d.callbacks = new Callbacks(d.cc, collision_callback);
	//
	// Special waypoint IDs
	d.weeds[d.LT] = 666; // Left Teleport
	d.weeds[d.RT] = 667; // Right Teleport
	d.weeds[d.TM] = 802; // Traffic Man / Snail Lair
	//
	// Set bg colour
	d.bg.r = d.bg.g = d.bg.b = 0x20;
	//
	// Starting time
	d.startingTime = getTimestamp();

} // setup_setup_data

static void setup_post_setup_data(PostInitData &d, GameData &gd) {
	// Create animation to sprite matcher
	d.matcher = new Matcher(gd.animdata->spritehold);
} // setup_post_setup_data
