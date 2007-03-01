#ifndef _WAYPOINT_HPP_
#define _WAYPOINT_HPP_

#include "Sprite.hpp"

class Waypoint : public Sprite {
	unsigned char available_directions;

	public:
	enum Waypoint_Direction {
		  UP    = 0x01
		, RIGHT = 0x02
		, DOWN  = 0x04
		, LEFT  = 0x08
	};
	bool CollisionCheck(Sprite *s);
	static void AICallback(Sprite *self, Sprite *actor, void *closure);
	static void TeleportCallback(Sprite *self, Sprite *actor, void *closure);
	Waypoint(int x, int y, unsigned char available_directions,
		spriteid_t id);
	Waypoint(int _x, int _y, bool _up, bool _down, 
		 bool _left, bool _right, spriteid_t id);
	unsigned char getAvailableDirections(void);
	bool canGoUp(void);
	bool canGoRight(void);
	bool canGoDown(void);
	bool canGoLeft(void);
	friend std::ostream &operator<<(std::ostream&, Waypoint&);
};

#endif
