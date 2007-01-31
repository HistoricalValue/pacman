#ifndef _OBSTACLESPRITE_HPP_
#define _OBSTACLESPRITE_HPP_

#include "Sprite.hpp"
#include "GameSprite.hpp"
#include <list>

class ObstacleSprite : public Sprite {
   std::list<GameSprite*> pushable;

public:
   void AddPushable (GameSprite* s);
   void RemovePushable (GameSprite* s);
   void Move (int dx, int dy);
   static void WhenHit (Sprite* self, Sprite* actor, void* unused);
   ObstacleSprite(int x, int y, AnimationFilm* f, spriteid_t id);
};

#endif
