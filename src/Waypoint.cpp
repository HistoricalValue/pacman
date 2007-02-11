#include "Waypoint.hpp"
#include "AI.hpp"
#include "Ghost.hpp"
#include <iostream>

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
	SetCollisionCallback(&AICallback);
}

Waypoint::Waypoint(int x, int y, unsigned char _available_directions,
	spriteid_t id)
:
	Sprite(x, y, NULL, id), available_directions(_available_directions)
{ }

bool Waypoint::CollisionCheck(Sprite *s) {
	//Absolute collision
	if(x == s->GetX() && y == s->GetY())
		return true;
	return false;
}

void Waypoint::AICallback(Sprite *self, Sprite *actor, void *closure) {
	AI::Think(dynamic_cast<Waypoint*>(self), dynamic_cast<Ghost*>(actor));
}

void Waypoint::TeleportCallback(Sprite *self, Sprite *actor, void *closure) {
	Waypoint *other = static_cast<Waypoint*>(closure);
	actor->SetPosition(
		self->GetX() - other->GetX() < 0 ? other->GetX() - 1 : other->GetX() + 1,
		other->GetY()
	);
}

bool Waypoint::canGoUp   (void) { return available_directions & UP;    }
bool Waypoint::canGoRight(void) { return available_directions & RIGHT; }
bool Waypoint::canGoDown (void) { return available_directions & DOWN;  }
bool Waypoint::canGoLeft (void) { return available_directions & LEFT;  }

unsigned char Waypoint::getAvailableDirections(void)
	{ return available_directions; }

std::ostream& operator<<(std::ostream& o, Waypoint& w) {
	static char const wayp[] = "Waypoint:",
	 lines[] = "----------",
	 xy[] = "{x,y} = {",
	 comma = ',',
	 rbrace = '}',
	 id[] = "id = ",
	 dirs[] = "up/right/down/left : ",
	 tab = '\t';
	return
	 o<<lines<<std::endl<<wayp<<std::endl<<tab<<id<<w.id<<std::endl<<
	 tab<<xy<<w.x<<comma<<w.y<<rbrace<<std::endl<<tab<<dirs<<
	 w.canGoUp()<<comma<<w.canGoRight()<<comma<<w.canGoDown()<<comma<<
	 w.canGoDown()<<std::endl<<lines;
} // operator<<
