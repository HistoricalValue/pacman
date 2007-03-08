#include "custompostinit_assign_smash_callbacks.hpp"
#include "death_pacman.hpp"

CPI_DEFINE(custompostinit_assign_smash_callbacks) {
	_gcoca *gkoka = new _gcoca;
	gkoka->cc = gd.cc;
	gkoka->akmovs = &gd.akmovs;
	gkoka->ghost = &gd.ghost;
	gkoka->filmhold = gd.animdata->filmhold;
	gkoka->animhold = gd.animdata->animhold;
	gkoka->sch = gd.sch;
	gkoka->gs = gd.stats;
	gkoka->left_right = // waypoint that sends snails away from the lair
	 gd.animdata->wayhold->getWaypoint(d.weeds[d.TM]);
	gkoka->down = // a waypoint that sends snails in the lair
	 gd.animdata->wayhold->getWaypoint(d.weeds[d.TI]);
	gkoka->lair = // a waypoint that is inside the lair
	 gd.animdata->wayhold->getWaypoint(WAYPOINT_LAIR);
	gkoka->initpos = // the initial positions of the special sprites
	 &gd.custom->initpos;
	gkoka->theatre_mode = &gd.bools->theatre_mode; // IO status flag

	// Assign pacman shmash callback
	gd.pacman->SetOnSmashed(
	 pacman_death_by_smash_callback,
	 new _shca( gkoka )
	);
} // custompostinit_assign_smash_callbacks
