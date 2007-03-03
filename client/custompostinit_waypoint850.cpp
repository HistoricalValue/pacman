#include "custompostinit_waypoint850.hpp"
#include "ghost.hpp"
CPI_DEFINE(custompostinit_waypoint850) {
	struct _gcoca *pkoka = new _gcoca;
	pkoka->cc = d.cc;
	pkoka->akmovs = &gd.akmovs;
	pkoka->ghost = &gd.ghost;
	pkoka->filmhold = gd.animdata->filmhold;
	pkoka->animhold = gd.animdata->animhold;
	pkoka->sch = gd.sch;
	pkoka->left_right =gd.animdata->wayhold->getWaypoint(d.weeds[d.TM]);
	pkoka->down = gd.animdata->wayhold->getWaypoint(d.weeds[d.TI]);
	gd.animdata->wayhold->getWaypoint(WAYPOINT_UNEATER)->
	 SetCollisionCallback(ghost_uneating_callback, pkoka);
}
