#include "Ghost.hpp"

// Implementation headers
#include "commons.hpp"
#include "config.h"

void Ghost::SetState(ghoststate_t _state) {
	state = _state;
}

ghoststate_t Ghost::GetState(void) {
	return state;
}

bool Ghost::isControlled(void) {
	return controlled;
}

void Ghost::setControlled(bool _controlled) {
	controlled = _controlled;
}

Ghost::Ghost(int x, int y, AnimationFilm *f, spriteid_t id) :
GameSprite(x, y, f, id) {
	state = NORMAL;
	controlled = false;
}

bool Ghost::CollisionCheck(Sprite *o) {
	bool result;
	if (state != RETREAT) {
		if (o->getID() == PACMAN) {
			register SDL_Rect original = frameBox;
			register int oldx = x;
			register int oldy = y;
			register const int offset = 10;
			x += offset;
			y += offset;
			frameBox.w -= offset<<1;
			frameBox.h -= offset<<1;
			result = Sprite::CollisionCheck(o);
			frameBox = original;
			x = oldx;
			y = oldy;
		} else
			result = Sprite::CollisionCheck(o);
	} else 
		result = false;
	return result;
}

Ghost::~Ghost(void) { }

