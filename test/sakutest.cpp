#define __SAKUTEST_001__

#ifdef __SAKUTEST_001__
#include "sakutest.hpp"
#include "Animator.hpp"

namespace sakutest{
data d;

} //namespace sakutest

using namespace sakutest;

unsigned long int total_time = 0;
unsigned short int numloops = 0;

timestamp_t loop_time;
timestamp_t const* cs454_2006::currTime = &loop_time;

int main(int argc, char *argv[]) {
	memset(&d, 0, sizeof(d));
	setup(d);
	atexit(cleanup);

	SDL_Event event;
	timestamp_t starting_time;
	const timestamp_t sdl_delay = 1000/60 + 1;
	while (true) {
		starting_time = loop_time = cs454_2006::getTimestamp();
		// redraw background
		SDL_FillRect(d.screen, NULL, *d.bgcolor);

		if (SDL_PollEvent(&event))
			handleEvent(d, event);

		// progress animations
		d.currTime = cs454_2006::getTimestamp();
		AnimatorHolder::Progress(d.currTime);
		d.pacmov->progress(d.currTime);
		d.snailymov->progress(d.currTime);
		// collision checking happens internally

		d.moves[0]=d.moves[1];
		// draw final result
		d.animation_data->plathold->displayPlatforms(d.screen);
		d.animation_data->spritehold->displaySprites(d.screen);
//		d.animation_data->wayhold->display(d.screen);

		timestamp_t diff =
		 timestamp_diff(cs454_2006::getTimestamp(),
		 starting_time);
		SDL_Flip(d.screen);
		SDL_Delay(diff > sdl_delay? diff : sdl_delay-diff);

		total_time += (getTimestamp() - starting_time);
		numloops++;
	}


	return 0;
}


namespace sakutest {
using namespace cs454_2006;
void cleanup(void) {
	db("TTF Quit");
	TTF_Quit();
	db("SDL Quit");
	SDL_Quit();
	double avg;
	avg = static_cast<double>(total_time)/numloops;
	std::cerr<<"Avergae gaim loop duration: "<<avg<<std::endl<<
	 "Average fps: "<<(1000/avg)<<std::endl;
}

void create_bgcolor(data& d) {
	d.bgcolor = new Uint32(
	 SDL_MapRGB(d.screen->format, 0x20, 0x20, 0x20)
	);
}

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



void collision_callback(Sprite* self, Sprite* actor, void* c) {
	data* d = static_cast<data*>(c);
	nf(!d, "No data argument passed to callback");

	ObstacleSprite* obst = dynamic_cast<ObstacleSprite*>(self);
	nf(!obst, "Self sprite is not an ObstacleSprite");
	GameSprite* aktor = dynamic_cast<GameSprite*>(actor);
	nf(!aktor, "Actor sprite is not a GameSprite");
	d->pacmov->collided(aktor);
	d->snailymov->collided(aktor);
	obst->WhenHit(self, actor, 0);
}

using namespace cs454_2006;

int after_move_call::operator() (Animator* imprtnt_argmnt_dnt_ignr) const {
	cc->Check();
	return 0;
}

after_move_call::after_move_call(void) : cc(CollisionChecker::Singleton()){}

} // namespace sakutest
#endif
