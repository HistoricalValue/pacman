#ifndef _GHOST_HPP_
#define _GHOST_HPP_

#include "GameSprite.hpp"

enum ghoststate_t {
	NORMAL 	= 0,
	SCARED 	= 1, 
	RETREAT = 2
};

class Ghost : public GameSprite {
	ghoststate_t state;

	void SetState(ghoststate_t _state);
	ghoststate_t GetState(void);

	Ghost(int x, int y, AnimationFilm *f, spriteid_t id);
};

#endif
