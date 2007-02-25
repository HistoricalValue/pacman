#include "CustomPostinit_Commons.hpp"

CPI_DEFINE(custompostinit_unregister_waypoint_888) {
	Sprite *waypoint888 = gd.animdata->wayhold->getWaypoint(888);
	gd.cc->Cancel(waypoint888, gd.sss[1]);
	gd.cc->Cancel(waypoint888, gd.sss[2]);
	gd.cc->Cancel(waypoint888, gd.sss[3]);
	gd.cc->Cancel(waypoint888, gd.sss[4]);
	gd.cc->Commit();
}

