#include "ObstacleSprite.hpp"
#include "CollisionChecker.hpp"
#include <iostream>

void ObstacleSprite::Move (int dx, int dy) {
	Sprite::Move(dx, dy);
	
	std::list<GameSprite*>::iterator i;
	for(i = pushable.begin(); i != pushable.end(); i++) {
		if(dx) {
			if((*i)->CollisionCheck(this)){
		/*		int touchdx;
				if(dx > 0)
					touchdx = (this->x + this->GetW()) - (*i)->GetX();
				else
					touchdx = this->x - ((*i)->GetX() + (*i)->GetW());
		*/	
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
			/*	int touchdy;
				if(dy > 0)
					touchdy = (this->y + this->GetH()) - (*i)->GetY();
				else
					touchdy = this->y - ((*i)->GetY() + (*i)->GetH());
			*/
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

// Constructor
ObstacleSprite::ObstacleSprite(int x, int y, AnimationFilm *f,
 spriteid_t id) : Sprite(x, y, f, id)
{
	SetCollisionCallback(&WhenHit);
}
