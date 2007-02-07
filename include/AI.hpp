#ifndef _AI_HPP_
#define _AI_HPP_

#include "Sprite.hpp"

void StalkerAI(Sprite *self, Sprite *ghost, void *aidata);
void ChickenAI(Sprite *self, Sprite *ghost, void *aidata);
void RandomAI(Sprite *self, Sprite *ghost, void *aidata);

#endif
