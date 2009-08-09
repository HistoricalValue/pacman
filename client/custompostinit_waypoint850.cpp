#include "custompostinit_waypoint850.hpp"
#include "_ghost.hpp"
CPI_DEFINE(custompostinit_waypoint850) {
	struct _gcoca *pkoka = getacoca(d, gd);
	gd.animdata->wayhold->getWaypoint(WAYPOINT_UNEATER)->
	 SetCollisionCallback(ghost_uneating_callback, pkoka);
}
