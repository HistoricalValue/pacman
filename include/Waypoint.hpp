#ifndef _WAYPOINT_HPP_
#define _WAYPOINT_HPP_

#include "Sprite.hpp"

class Waypoint : public Sprite {
	bool up, down, left, right;

	public:
	bool CollisionCheck(Sprite *s);
	Waypoint(int _x, int _y, bool _up, bool _down, 
		 bool _left, bool _right, spriteid_t id);
	
};

#endif
