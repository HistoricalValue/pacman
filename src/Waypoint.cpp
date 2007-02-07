#include "Waypoint.hpp"

Waypoint::Waypoint(int _x, int _y, bool _up, bool _down, 
		   bool _left, bool _right, spriteid_t id) 
		   : Sprite( _x, _y, NULL, id),
		     available_directions(0)
{
	SetVisibility(false);
	available_directions |= _up    ? UP    : 0x0;
	available_directions |= _right ? RIGHT : 0x0;
	available_directions |= _down  ? DOWN  : 0x0;
	available_directions |= _left  ? LEFT  : 0x0;
}

Waypoint::Waypoint(int x, int y, unsigned char _available_directions,
	spriteid_t id)
:
	Sprite(x, y, NULL, id), available_directions(_available_directions)
{ }

bool Waypoint::CollisionCheck(Sprite *s) {
	//Absolute collision
	if(x == s->GetX() && y == GetY())
		return true;
	return false;
}

void Waypoint::AICallback(Sprite *self, Sprite *actor, void *closure) {
}

bool Waypoint::canGoUp   (void) { return available_directions & UP;    }
bool Waypoint::canGoRight(void) { return available_directions & RIGHT; }
bool Waypoint::canGoDown (void) { return available_directions & DOWN;  }
bool Waypoint::canGoLeft (void) { return available_directions & LEFT;  }
