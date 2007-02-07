#include "Sprite.hpp"

bool Sprite::CollisionCheck(Sprite *s) {
	int left1, left2, right1, right2,
	    up1, up2, down1, down2;
	
	left1 = x;
	right1 = x + frameBox.w;
	up1 = y;
	down1 = y + frameBox.h;

	left2 = s->x;
	right2 = s->x + s->frameBox.w;
	up2 = s->y;
	down2 = s->y + s->frameBox.h;

	if(down1 <= up2 	||
	   up1 >= down2 	||
	   right1 <= left2	||
	   left1 >= right2	)
		return false;
	
	return true;
}


void Sprite::Display(SDL_Surface *dest) {
	SDL_Rect at = {x, y};
	currFilm->DisplayFrame(dest, &at, frameNo);
}


void Sprite::SetWH(int _w, int _h) { frameBox.w = _w, frameBox.h = _h; }
void Sprite::SetFrame (char i) {	
	if (currFilm) if (i != frameNo) {
		assert(i < currFilm->GetTotalFrames());
		frameBox = currFilm->GetFrameBox(frameNo = i);
	}
}
int  Sprite::GetX(void) const { return x; }
int  Sprite::GetY(void) const { return y; }
int  Sprite::GetW(void) const { return frameBox.w; }
int  Sprite::GetH(void) const { return frameBox.h; }
char Sprite::GetFrame (void) const { return frameNo; }
void Sprite::SetVisibility (bool v) { isVisible = v; }
bool Sprite::IsVisible (void) const { return isVisible; }

void Sprite::NotifyCollision (Sprite* target) {
	if (onCollision)
		(*onCollision)(this, target, collisionClosure);
}
void Sprite::SetPosition(int _x, int _y) { x = _x, y = _y; }
void Sprite::Move(int dx, int dy) { x += dx; y += dy; }

std::ostream& operator << (std::ostream& o, Sprite& s) {
	static const char comma = ',', rbrace = '}';
	static const char
	 sprite[] = "Sprite ",
	 xyz[] = "{x,y,z} = {",
	 film[] = "Animation film {id,addr} = {";

	return o << sprite << s.id << std::endl <<
	 xyz << s.x << comma << s.y << rbrace << std::endl <<
	 film << s.currFilm->GetId() << comma << s.currFilm << rbrace;
} // <<

void Sprite::SetCollisionCallback (CollisionCallback f, void* c) { 
	onCollision = f, collisionClosure = c;
}

spriteid_t Sprite::getID(void) const { return id; }

// Constructor
Sprite::Sprite (int _x, int _y, AnimationFilm* film, spriteid_t _id): 
 x(_x), y(_y), currFilm(film), isVisible(true),
 frameNo(-1), id(_id)
{
	SetFrame(0);
}

// Destructor
Sprite::~Sprite(void) { }
