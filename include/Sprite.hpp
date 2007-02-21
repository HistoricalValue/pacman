#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

#include <ostream>
#include <iostream>

#include "SDL/SDL.h"
#include "AnimationFilm.hpp"

typedef unsigned long spriteid_t;

class Sprite {
	public :
	typedef void (*CollisionCallback)(Sprite* self, Sprite* actor,
	 void* closure);
	protected :
	int			x,y;
	AnimationFilm*		currFilm;
	bool			isVisible;
	char			frameNo;
	spriteid_t		id;
	SDL_Rect		frameBox;
	CollisionCallback	onCollision;
	void*			collisionClosure;
	
	public:
	// TODO remove
	void SetWH(int _w, int _h) ;
	void SetFrame (char i) ;
	int  GetX(void) const ;
	int  GetY(void) const ;
	int  GetW(void) const ;
	int  GetH(void) const ;
	char GetFrame (void) const ;
	void SetVisibility (bool );
	bool IsVisible (void) const ;
	virtual bool CollisionCheck (Sprite* s);
	void SetCollisionCallback (CollisionCallback f,
	 void* c = static_cast<void*>(0));
	virtual void NotifyCollision (Sprite* target) ;
	virtual void SetPosition(int _x, int _y);
	virtual void Move(int dx, int dy);
	void Display(SDL_Surface *dest);
	spriteid_t getID(void) const;
	AnimationFilm *getFilm(void) const;
	void setFilm(AnimationFilm*);
	friend std::ostream& operator << (std::ostream&, Sprite& s);

	Sprite (int _x, int _y, AnimationFilm* film, spriteid_t _id);
	virtual ~Sprite(void);
};

#endif
