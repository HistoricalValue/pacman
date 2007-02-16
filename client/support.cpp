#include "support.hpp"

int Callbacks::_amc::operator() (Animator *a) const {
	return 0;
}

Callbacks::Callbacks( CollisionChecker *_cc, Sprite::CollisionCallback scc):
 cc(_cc), amc(), coca(scc), cocaclo() { }
Callbacks::~Callbacks(void) { }
Callbacks::_amc::_amc(void) { }
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

void collision_callback(Sprite *callbacker, Sprite *stoocker, void *c) {
	// Retrive closure data
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

Sprite* Matcher::operator() (Animation* a) const {
	bool noRun = false;
	spriteid_t spid;
	animid_t anid = a->GetId();
	if (anid == 1) { // evil box
		spid = 1002;
	} else if (anid >= 2002 && anid <= 2005 ) { // cartman frame range
		noRun = true;
	} else if ((anid >= 1002 && anid <= 1005)) { // cartman mov
		// do not run those ones
		noRun = true;
	} else if (anid >= 3000 && anid <= 3023) { // ghost snailz
		noRun = true;
	} else if (anid == 3024) { // choco yum
		spid = 1015;
	} else {
		spid = a->GetId();
		spid = anid;
	}
	return noRun ? NULL : sh->getSprite(spid);
}
Matcher::Matcher(SpriteHolder* _sh) : Anim2SpriteMatcher(_sh) { }
Matcher::~Matcher(void) { }

