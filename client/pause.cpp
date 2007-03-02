#include "pause.hpp"

#include "AnimatorHolder.hpp"
#include "ActorMovement.hpp"

struct _susres :
 public std::unary_function<std::pair<GameSprite *const, ActorMovement*>&,
 void> 
{
	enum mode {suspend, resume};
	result_type operator()(argument_type);
	_susres &operator[](enum mode);
	_susres &operator=(timestamp_t);
	_susres(void);
	~_susres(void);
	private :
	enum mode m;
	timestamp_t t;
}; // struct _susres

void cleanPause(GameData &d, bool &paused) {
	static _susres susres;
	if (paused) { // un-pause operations
		db("Unpausing");
		// Unsuspend all ex-running animators
		AnimatorHolder::resumeAllExRunning(d.currTime);

		// Resume all actor movement instances
		std::for_each(d.akmovs.begin(), d.akmovs.end(),
		 susres[susres.resume] = d.currTime);

		// Resume the scheduler
		d.sch->resume(d.currTime);
	} else { // pause operations
		db("Pausing");
		// Suspend all running animators
		AnimatorHolder::suspendAllRunning(d.currTime);

		// Suspend all actor movement instances
		std::for_each(d.akmovs.begin(), d.akmovs.end(),
		 susres[susres.suspend] = d.currTime);

		// Suspend scheduler
		d.sch->suspend(d.currTime);
	}
	// Set paused state opposite than before
	paused = !paused;
} // cleanPause

// Susres implementation -------------------------------------------------
_susres::_susres(void) : m(suspend), t(0) { }

_susres::result_type
_susres::operator()(argument_type p) {
	ActorMovement *animator = p.second;
	// Just for posing
	void (ActorMovement::*funk)(timestamp_t) = NULL;
	switch (m) {
		case suspend : funk = &ActorMovement::suspend; break;
		case resume : funk = &ActorMovement::resume; break;
	}
	(animator->*funk)(t);
} // susres()

_susres &_susres::operator[](enum mode _m) { m = _m; return *this; }
_susres &_susres::operator=(timestamp_t _t) { t = _t; return *this; }
_susres::~_susres(void) { }
