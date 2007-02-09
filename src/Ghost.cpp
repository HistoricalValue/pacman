#include "Ghost.hpp"

void Ghost::SetState(ghoststate_t _state) {
}

ghoststate_t Ghost::GetState(void) {
	return NORMAL;
}

Ghost::Ghost(int x, int y, AnimationFilm *f, spriteid_t id) :
GameSprite(x, y, f, id) {
}
