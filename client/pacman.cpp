#include "SDL/SDL_ttf.h"
#include "client.hpp"
#include "support.hpp"
#include "config.h"
#include "inputControl.hpp"
#include "AnimatorHolder.hpp"
#include "CustomPostinit.hpp"
#include "StartingScreen.hpp"

static void setup_setup_data(InitData &);
static void setup_post_setup_data(PostInitData &, GameData &);
static void gaim_loop(GameData&);
static void screen_setup(InitData const&, GameData &);
static void showWiener(GameData &);
static void credits(GameData &);

int main_pac(int argc, char *argv[]) {
	// Clean exit first
	atexit(cleanup);
	
	InitData d;
	PostInitData pd;
	GameData gd;
	screen_setup(d, gd);

	// Show splash/loading screen
	SDL_Surface *splash = 
	 SurfaceLoader::getInstance()->loadSurface(SPLASH_SCREEN);
	nf(!splash, "Unable to load splash screen");
	blit(splash, gd.screen, 0, 0);
	SDL_Flip(gd.screen);

	// Initialisation data and initial setup
	setup_setup_data(d);
	setup(d, gd);
	// Post-setup data and post-setup
	setup_post_setup_data(pd, gd);
	post_setup(pd, d, gd);

	// Manage splash screen
	ShowStartingScreen(splash, gd.screen, *gd.bools, gd.akmovs,
	 d.startingTime);
	// Start game loop
	gaim_loop(gd);

	// conclusion 
	if (gd.bools->won)
		showWiener(gd);
	SDL_Delay(5000);

	credits(gd);

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
	d.weeds[d.LT] = WAYPOINT_LEFT_TELEPORTER; // Left Teleport
	d.weeds[d.RT] = WAYPOINT_RIGHT_TELEPORTER; // Right Teleport
	// Traffic Man / Send snails away
	d.weeds[d.TM] = WAYPOINT_TRAFICMAN_AWAY;
	// traffic man / send snails inside lair
	d.weeds[d.TI] = WAYPOINT_TRAFICMAN_INSIDE;
	// The lair target to lead ghosts back inside
	d.weeds[d.LR] = WAYPOINT_GET_BACK;
	//
	// Set bg colour
	d.bg.r = 0x20;
	d.bg.g = 0x20;
	d.bg.b = 0x20;
	//
	// Set IDs of power ups
	d.pids.push_back(5000);
	d.pids.push_back(5001);
	d.pids.push_back(5002);
	d.pids.push_back(5003);
	// Starting time
	d.startingTime = getTimestamp();

} // setup_setup_data

static void setup_post_setup_data(PostInitData &d, GameData &gd) {
	// Create animation to sprite matcher
	d.matcher = new Matcher(gd.animdata->spritehold);

	// Give custom post init functions to set-up-er
	registerCustomPostinit(d.user);
} // setup_post_setup_data

static timestamp_t currTime;
static void gaim_loop(GameData &d) {
	register const timestamp_t loop_cap = 1000/60 + 1;
	register timestamp_t timesand;
	register uint64_t total_sand = 0;
	register uint16_t numloops = 0;
	InputControl inputControl(d);
	while (!d.bools->exit && !d.bools->won) {
		// get gaim loop starting time
		d.currTime = timesand = currTime = getTimestamp();

		// Handle input events
		inputControl();

		if (!d.bools->paused) {
			// Progress everything
			AnimatorHolder::Progress(timesand);
			std::for_each(d.akmovs.begin(), d.akmovs.end(),
			 AnimatorProgressor(timesand));
			// collision checking happens through callbacks
			d.cc->Commit();
		
			// Run scheduled tasks
			d.sch->check(timesand);

			// Draw on the screen
			SDL_FillRect(d.screen, NULL, d.bg);
			d.animdata->plathold->displayPlatforms(d.screen);
			d.animdata->spritehold->displaySprites(d.screen);
			d.stats->Draw(d.screen);
			SDL_Flip(d.screen);
		}

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
static void screen_setup(InitData const &d, struct GameData &r) {
	r.screen = SDL_SetVideoMode(
	 d.screen.width,
	 d.screen.height,
	 d.screen.bpp,
	 d.screen.flags
	);
} // screen_setup

static void showWiener(GameData &gd) {
	TTF_Font *font = TTF_OpenFont("./resources/fonts/ARCADE.TTF", 32);
	nf(!font, "Could not load font ./resources/fonts/ARCADE.TTF");
	const SDL_Color color = {0x60, 0xa0, 0xc0};
	SDL_Surface *text[] = {
		  TTF_RenderUTF8_Blended(font, "Baby,", color)
		, TTF_RenderUTF8_Blended(font, "you are the Wiener!", color)
		, TTF_RenderUTF8_Blended(font, "gradz lol ^_^", color)
	};

	register SDL_Rect destr;
	for (register size_t i = 0;i<sizeof(text)/sizeof(SDL_Surface*);i++){
		nf(!text[i], "Could not render text");
		destr.x = 520, destr.y = 370 + (i<<5);
		SDL_BlitSurface(text[i], NULL, gd.screen, &destr);
	}

	SDL_Flip(gd.screen);

} // showWiener

static void credits(GameData &) {
	//TODO complete
} // credits
