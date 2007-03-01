#ifndef _OBSTACLEPLATFORM_HPP_
#define _OBSTACLEPLATFORM_HPP_

#include "GameSprite.hpp"
#include "ObstacleSprite.hpp"
#include "CollisionChecker.hpp"
#include "SDL/SDL.h"
#include <list>

class ObstaclePlatform {
       std::list<ObstacleSprite*> sprites;
       unsigned x, y;

       void AddPushable (GameSprite *s) ;
       void RemovePushable (GameSprite *s) ;

public:
       void SetCollisionCheck (GameSprite *actor, bool flag) ;
       void Display(SDL_Surface *dest) ;
       void Add (ObstacleSprite *s, unsigned rx, unsigned ry) ;
       void Move (int dx, int dy) ;
       ObstaclePlatform(unsigned _x, unsigned _y);
};

#endif
