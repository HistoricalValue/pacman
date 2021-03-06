#include "support.hpp"
#include<set>

// Implementation headers
#include "Dot.hpp"
#include "config.h"


int Callbacks::_amc::operator() (Animator *a) const {
	cc->Check();
	return 0;
}

Callbacks::Callbacks( CollisionChecker *_cc, Sprite::CollisionCallback scc):
 cc(_cc), amc(cc), coca(scc), cocaclo() { }
Callbacks::~Callbacks(void) { }
Callbacks::_amc::_amc(CollisionChecker *_cc) : cc(_cc) { }
Callbacks::_amc::~_amc(void) { }

void cleanup(void) {
	db("TTF Quit");
	TTF_Quit();
	db("SDL Quit");
	SDL_Quit();
}

amc_t &Callbacks::get_amc(void) {
	return amc;
} // Callback::get_amc

// Obstacle - Game sprite collision callback
void collision_callback(Sprite *callbacker, Sprite *stoocker, void *c) {
	// Retrive closure data
	nf(!c, "Closure is NULL");
	_cocaclo *cocaclo = CAST(_cocaclo*, c);

	// Retrieve obstacle
	ObstacleSprite *o = DYNCAST(ObstacleSprite*, callbacker);
	nf(!o, "Callbacker sprite is not the right type.");
	// Retrieve actor
	GameSprite *a = DYNCAST(GameSprite*, stoocker);
	nf(!a, "Stoocker sprite is not the right type.");

	// Inform the appropriate ActorMovement
	(*cocaclo->akmovs)[a]->collided(a);

	// Call obstacle's callback to do the rest
	o->WhenHit(o, a, 0);
} // collision_callback

struct _cocaclo &Callbacks::get_cocaclo() { return cocaclo; }
Sprite::CollisionCallback Callbacks::get_coca() { return coca; }

_cocaclo::_cocaclo(void) : 
 akmovs(static_cast<std::map<GameSprite*, ActorMovement*>*>(0)) { }
_cocaclo::~_cocaclo(void) { }

Sprite *Matcher::operator() (Animation *a) const {
	bool noRun = false;
	spriteid_t spid;
	animid_t anid = a->GetId();
	if (anid >= 3 && anid <= 50) { // static walls - no anim
		noRun = true;
	} else if (anid >= 2002 && anid <= 2005 ) { // cartman frame range
		noRun = true;
	} else if ((anid >= 1002 && anid <= 1005)) { // cartman mov
		// do not run those ones
		noRun = true;
	} else if (anid >= 3000 && anid <= 3100) { // ghost snailz
		noRun = true;
	} else if (anid == 7000) { // choco yum
		spid = 7000;
	} else if (anid >= 4000 && anid < 5000) { // dot animation
		spid = anid - 2000;
	} else if (anid >= 5000 && anid < 6000) { // power ups
		spid = anid;
	} else {
		noRun = true;
//		spid = a->GetId();
//		spid = anid;
	}
	return noRun ? NULL : sh->getSprite(spid);
}
Matcher::Matcher(SpriteHolder *_sh) : Anim2SpriteMatcher(_sh) { }
Matcher::~Matcher(void) { }

AnimatorProgressor::AnimatorProgressor(timestamp_t _timesand) :
 timesand(_timesand) { }

AnimatorProgressor::result_type 
AnimatorProgressor::operator() (argument_type p)
{
	p.second->progress(timesand);
} // AnimatorProgressor::()

void DotAnimatorCallback(Animator *a, void *c) {
	MovingAnimator *ma = DYNCAST(MovingAnimator*, a);
	nf(!ma, "Dot animator is not a moving animator.");
	// The dot sprite
	Sprite *s = ma->GetSprite();
	Dot *d = DYNCAST(Dot*, s);
	if (!d) {
		std::cerr<<s->getID();
		nf(-1, "The animator's sprite is not a dot sprite.");
	}
	
	if (d->animationIsFinished()) {
		ma->getAnimation()->SetDx(
		 -ma->getAnimation()->GetDx());
		ma->getAnimation()->SetDy(
		 -ma->getAnimation()->GetDy());

		d->resetNumberOfRepeats();
	} else
		++(*d);
} // DotAnimatorCallback

void Dot::collisionCallback(Sprite *dot, Sprite *stoocker, void *c) {
	if (dot->IsVisible()) if (c) {
		struct _coca &koka = *CAST(struct _coca*, c);
		nf(!koka.cc, "No collision checker provided.");
		nf(!koka.pacman, "No pacman provided.");
		nf(!dot, "Wtf");
		koka.cc->Cancel(dot, koka.pacman);
		dot->SetVisibility(false);

		// Give points to the player
		koka.stat->AddScore(POINTS_WORTH_DOT);
		*koka.won = koka.stat->EatDot();
		SoundManager::Singleton()->PlayEffect(4,DOT);
	}
} // collisionCallback
