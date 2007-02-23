#include "client.hpp"
#include "support.hpp"
#include "config.h"
#include "inputControl.hpp"
#include "AnimatorHolder.hpp"

static void setup_setup_data(InitData &);
static void setup_post_setup_data(PostInitData &, GameData &);
static void gaim_loop(GameData&);

int main_pac(int argc, char *argv[]) {
	// Clean exit first
	atexit(cleanup);
	
	// Initialisation data and initial setup
	InitData d;
	setup_setup_data(d);
	GameData &gd = setup(d);
	// Post-setup data and post-setup
	PostInitData pd;
	setup_post_setup_data(pd, gd);
	post_setup(pd, d, gd);

	gaim_loop(gd);
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
	d.speeds.assign(5, 0);
	d.speeds[ss_pacman] = 1001;
	d.speeds[ss_stalker] = 3003;
	d.speeds[ss_kieken] = 3004;
	d.speeds[ss_random] = 3005;
	d.speeds[ss_retard] = 3006;
	//
	// Animation IDs for each special sprite
	d.anids.assign(5, *new AnimationIDs);
	for (size_t i = 0; i < 4; i++) {
		// Pacman
		d.anids[ss_pacman].mv[i] = (1002 + i);
		d.anids[ss_pacman].fr[i] = (2002 + i);
		// Stalker
		d.anids[ss_stalker].mv[i] = (3000 + i);
		d.anids[ss_stalker].fr[i] = (3004 + i);
		// chicken
		d.anids[ss_kieken].mv[i] = (3010 + i);
		d.anids[ss_kieken].fr[i] = (3014 + i);
		// random
		d.anids[ss_random].mv[i] = (3020 + i);
		d.anids[ss_random].fr[i] = (3024 + i);
		// retard	
		d.anids[ss_retard].mv[i] = (3030 + i);
		d.anids[ss_retard].fr[i] = (3034 + i);
	}
	//
	// Point to collision checker
	// TODO -- Low -- change singleton policy
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

static timestamp_t currTime;
static void gaim_loop(GameData &d) {
	register const timestamp_t loop_cap = 1000/60 + 1;
	register timestamp_t timesand;
	bool exit = false;
	register uint64_t total_sand = 0;
	register uint16_t numloops = 0;
	while (!exit) {
		// get gaim loop starting time
		d.currTime = timesand = currTime = getTimestamp();

		// Handle input events
		inputControl(d, &exit);

		// Progress everything
		AnimatorHolder::Progress(timesand);
		std::for_each(d.akmovs.begin(), d.akmovs.end(),
		 AnimatorProgressor(timesand));
		// collision checking happens through callbacks
		d.cc->Commit();

		// Draw on the screen
		SDL_FillRect(d.screen, NULL, d.bg);
		d.animdata->plathold->displayPlatforms(d.screen);
		d.animdata->spritehold->displaySprites(d.screen);
		// if one wants to display the junctions, they should
		// first set the Waypoint.bug
		SDL_Flip(d.screen);

		// Cap gaim loop speed
		timestamp_t sanddiff = timestamp_diff(
		 cs454_2006::getTimestamp(), timesand);
		SDL_Delay(sanddiff > loop_cap ? 0 :
		 timestamp_diff(loop_cap, sanddiff));

		// Time statistics
		total_sand += timestamp_diff(getTimestamp(), timesand);
		numloops++;
	} // gaim loop while

	double loop_avg = CAST(double, total_sand) / numloops;
	std::cerr << "Average gaim loop duration: " << loop_avg <<
	 std::endl << "Average fps: " << (1000 / loop_avg) << std::endl;
} // gaim_loop

timestamp_t cs454_2006::getCurrentTime(void) { return currTime; }
