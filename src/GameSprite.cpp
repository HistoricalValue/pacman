#include "GameSprite.hpp"

void GameSprite::SetOnSmashed(SmashedCallback f, void *c)
{
	onSmashed = f, smashedClosure = c;
} // SetOnSmashed

void GameSprite::NotifySmashed(Sprite *who) {
	if (onSmashed)
		(*onSmashed)(this, who, smashedClosure);
} // NotifySmashed

void GameSprite::Move(int dx, int dy) {
	oldX = x;
	oldY = y;
	Sprite::Move(dx, dy);
} // Move

void GameSprite::BackOff(void) {
	x = oldX, y = oldY;
} // BackOff

// Constructor
GameSprite::GameSprite(int x, int y, AnimationFilm *f, spriteid_t id) :
 Sprite(x, y, f, id), onSmashed(NULL)
 { }

