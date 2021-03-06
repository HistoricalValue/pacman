#include "ObstacleSprite.hpp"
#include "CollisionChecker.hpp"
#include <iostream>
#include "Ghost.hpp"
#include "commons.hpp"

void ObstacleSprite::Move (int dx, int dy) {
	Sprite::Move(dx, dy);
	
	std::list<GameSprite*>::iterator i;
	for(i = pushable.begin(); i != pushable.end(); i++) {
		if(dx) {
			if((*i)->CollisionCheck(this)){
				(*i)->Move(dx, 0);
				CollisionChecker::Singleton()->Check();
				if((*i)->CollisionCheck(this)){
					(*i)->NotifySmashed(this);
					continue;
				}
			}
		}
		if(dy) {
			if((*i)->CollisionCheck(this)){
				(*i)->Move(0, dy);
				CollisionChecker::Singleton()->Check();
				if((*i)->CollisionCheck(this)){
					(*i)->NotifySmashed(this);
					continue;
				}
			}
		}
	}
}

void ObstacleSprite::AddPushable(GameSprite *s) {
	pushable.push_back(s);
}

void ObstacleSprite::RemovePushable(GameSprite *s){
	pushable.remove(s);
}

void ObstacleSprite::WhenHit(Sprite *self, Sprite *actor, void *_0) {
	dynamic_cast<GameSprite*>(actor)->BackOff();
}

bool ObstacleSprite::CollisionCheck(Sprite *s) {
	Ghost *ghost = DYNCAST(Ghost*, s);
	if (ghost) { // it is a ghost sprite
		// make sure it is not dead
		if (ghost->GetState() == RETREAT)
			return false;
	}
	return Sprite::CollisionCheck(s);
} // CollisionCheck

// Constructor
ObstacleSprite::ObstacleSprite(int x, int y, AnimationFilm *f,
 spriteid_t id) : Sprite(x, y, f, id)
{
	SetCollisionCallback(&WhenHit);
}
