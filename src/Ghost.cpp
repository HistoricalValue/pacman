#include "Ghost.hpp"

void Ghost::SetState(ghoststate_t _state) {
	state = _state;
}

ghoststate_t Ghost::GetState(void) {
	return state;
}

Ghost::Ghost(int x, int y, AnimationFilm *f, spriteid_t id) :
GameSprite(x, y, f, id) {
	state = NORMAL;
	Sprite::SetCollisionCallback(collision_callback);
}

Ghost::~Ghost(void) { }

void Ghost::collision_callback(Sprite *, Sprite *, void *c) {
	// It is called .. many times per ghost touch.
} // collision_callback
