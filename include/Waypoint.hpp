#ifndef _WAYPOINT_HPP_
#define _WAYPOINT_HPP_

#include "Sprite.hpp"

struct targets {
	Sprite *pacman;
	Sprite *lair;
}

class Waypoint : public Sprite {
	bool up, down, left, right;

	public:
	bool CollisionCheck(Sprite *s);
	static void AICallback(Sprite *self, Sprite *actor, void *closure);
	Waypoint(int _x, int _y, bool _up, bool _down, 
		 bool _left, bool _right, spriteid_t id);
	
};

#endif
