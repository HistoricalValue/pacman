#include "support.hpp"

int Callbacks::amc::operator() (Animator *a) const {
	return 0;
}

Callbacks::Callbacks(void) { }
Callbacks::~Callbacks(void) { }
Callbacks::amc::amc(CollisionChecker *_cc) : cc(_cc) { }
Callbacks::amc::~amc(void) { }

void cleanup(void) {
	db("TTF Quit");
	TTF_Quit();
	db("SDL Quit");
	SDL_Quit();
}
