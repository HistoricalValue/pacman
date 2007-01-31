#include "ObstaclePlatform.hpp"

void ObstaclePlatform::AddPushable (GameSprite* s) {
	std::list<ObstacleSprite*>::iterator i;
	for(i = sprites.begin(); i != sprites.end(); i++)
		(*i)->AddPushable(s);
}
void ObstaclePlatform::RemovePushable (GameSprite* s) {
	std::list<ObstacleSprite*>::iterator i;
		for(i = sprites.begin(); i != sprites.end(); i++)
			(*i)->RemovePushable(s);
}
void ObstaclePlatform::SetCollisionCheck (GameSprite* actor, bool flag) {
	std::list<ObstacleSprite*>::const_iterator i;
	for(i = sprites.begin(); i != sprites.end(); i++) { 
		if(flag) {
			CollisionChecker::Singleton()->Register(*i, actor);
			AddPushable(actor);
		} else {
			CollisionChecker::Singleton()->Cancel(*i, actor);
			RemovePushable(actor);
		}
	}
}

void ObstaclePlatform::Display(SDL_Surface *dest) {
	std::list<ObstacleSprite*>::const_iterator i;
	for(i = sprites.begin(); i != sprites.end(); i++)
		 (*i)->Display(dest);
}

void ObstaclePlatform::Add (ObstacleSprite* s, unsigned rx, unsigned ry) {
	sprites.push_back(s);
	s->SetPosition(x+rx, y+ry); // Positioned relatively to platform.
}

void ObstaclePlatform::Move (int dx, int dy) {
	std::list<ObstacleSprite*>::iterator i;
	for(i = sprites.begin(); i != sprites.end(); i++)
		(*i)->Move(dx, dy);
}

// Constructor
ObstaclePlatform::ObstaclePlatform(unsigned _x, unsigned _y) : x(_x), y(_y)
{ }
