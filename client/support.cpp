#include "support.hpp"

int Callbacks::_amc::operator() (Animator *a) const {
	return 0;
}

Callbacks::Callbacks( CollisionChecker *_cc, Sprite::CollisionCallback scc):
 cc(_cc), amc(), coca(scc), cocaclo(CAST(_cocaclo*, 0)) { }
Callbacks::~Callbacks(void) { }
Callbacks::_amc::_amc(CollisionChecker *_cc) : cc(_cc) { }
Callbacks::_amc::~_amc(void) { }

void cleanup(void) {
	db("TTF Quit");
	TTF_Quit();
	db("SDL Quit");
	SDL_Quit();
}

void collision_callback(Sprite *callbacker, Sprite *stoocker, void *c) {
	
} // collision_callback
