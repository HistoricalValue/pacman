#ifndef _BONUS_H_
#define _BONUS_H_

#include"commons.hpp"      
#include"GameStats.hpp"
#include"Sprite.hpp"
#include"CollisionChecker.hpp"

struct bcoca{
  GameStats *gs;
  CollisionChecker *cc;
};

extern void BonusCallback(Sprite *, Sprite *, 
			  void *c=CAST(void*,0));

#endif
