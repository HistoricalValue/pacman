/* WaypointHolder.hpp
 *
 * Holds all the waypoints. Can also be initialised by parsing a
 * configuration file.
 */

#ifndef __WaypointHolder_hpp__
#define __WaypointHolder_hpp__
#include <string>
#include <list>
#include "Waypoint.hpp"
#include "CollisionChecker.hpp"
#include "GameSprite.hpp"
typedef unsigned short int waypointid_t;
class WaypointHolder {
	public :
	WaypointHolder(std::string const &config_file_path);
	Waypoint *getWaypoint(waypointid_t id) const;
	std::list<Waypoint*> getWaypoints(void) const;
	void addWaypoint(Waypoint *w);
	void setCollision(GameSprite*, CollisionChecker*, bool);
	// For convencience
	void setBug(SDL_Surface*);
	void display(SDL_Surface*);
	private :
	std::list<Waypoint*> waypoints;
	SDL_Surface *bug;
};
#endif // __WaypointHolder_hpp__
