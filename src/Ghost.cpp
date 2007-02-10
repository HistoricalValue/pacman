#include "Ghost.hpp"

void Ghost::SetState(ghoststate_t _state) {
	state = _state;
}

ghoststate_t Ghost::GetState(void) {
	return state;
}

Ghost::Ghost(int x, int y, AnimationFilm *f, spriteid_t id) :
GameSprite(x, y, f, id) {
}
