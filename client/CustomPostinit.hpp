/* Registers the user postinit functions */

#ifndef __CustomPostinit_hpp__
#define __CustomPostinit_hpp__
#include "custompostinit_unregister_waypoint_888.hpp"
#include "custompostinit_waypoint850.hpp"
#include "custompostinit_start_obstplats.hpp"
#include "custompostinit_sound.hpp"
#include "custompostinit_stats.hpp"
template <typename _container>
void registerCustomPostinit(_container &c) {
	c.push_back(custompostinit_unregister_waypoint_888);
	c.push_back(custompostinit_waypoint850);
	c.push_back(custompostinit_start_obstplats);
	c.push_back(custompostinit_sound);
	c.push_back(custompostinit_stats);
} // registerCustomPostinit
#endif // __CustomPostinit_hpp__
