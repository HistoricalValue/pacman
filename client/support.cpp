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
	cocaclo->akmovs[a]->collided(a);

	// Call obstacle's callback to do the rest
	o->WhenHit(o, a, 0);
} // collision_callback

struct _cocaclo &Callbacks::get_cocaclo() { return cocaclo; }
Sprite::CollisionCallback Callbacks::get_coca() { return coca; }
