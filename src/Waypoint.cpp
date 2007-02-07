#include "Waypoint.hpp"

Waypoint::Waypoint(int _x, int _y, bool _up, bool _down, 
		   bool _left, bool _right, spriteid_t id) 
		   : Sprite( _x, _y, NULL, id)
{
	up = _up;
	down = _down;
	left = _left;
	right = _right;
	SetVisibility(false);
}

bool Waypoint::CollisionCheck(Sprite *s) {
	//Absolute collision
	if(x == s->GetX() && y == GetY())
		return true;
	return false;
}

static void AICallback(Sprite *self, Sprite *actor, void *closure) {
}
