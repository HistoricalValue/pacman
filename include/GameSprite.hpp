#ifndef _GAMESPRITE_HPP_
#define _GAMESPRITE_HPP_

#include "Sprite.hpp"

class GameSprite : public Sprite {
public:
	typedef void (*SmashedCallback)(GameSprite *s, 
	 Sprite *smasher, void *closure);
protected:
	int oldX, oldY;
	SmashedCallback onSmashed;
	void *smashedClosure;
	bool isSmashed;
public:
	void SetOnSmashed (SmashedCallback f,
	 void *c = static_cast<void*>(0));
	void NotifySmashed (Sprite *who);
	void Move (int dx, int dy);
	void BackOff (void);
	bool IsSmashed(void) const;
	GameSprite(int x, int y, AnimationFilm *f, spriteid_t id);
};

#endif
