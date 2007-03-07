#include "death_pacman.hpp"
#include "SoundManager.hpp"
#include "AnimatorHolder.hpp"
#include "reset.hpp"
#include "config.h"

struct ActorSuspender : public std::unary_function<
 std::pair<GameSprite *const, ActorMovement*>&, void> {
	 result_type operator()(argument_type);
	 ActorSuspender(timestamp_t);
	 private :
	 timestamp_t t;
}; // struct ActorSuspender
struct ActorResumer : public std::unary_function<
 std::pair<GameSprite *const, ActorMovement*>&, void> {
	 result_type operator()(argument_type);
	 ActorResumer(timestamp_t);
	 private :
	 timestamp_t t;
}; // struct ActorSuspender

void pacman_death_by_ghost_callback(Ghost *g, GameSprite *p, _gcoca *gkoka){
	// Super FX mode! Pause all ghosts and pacman
	
	register timestamp_t currTime = cs454_2006::getCurrentTime();

	// Theatre mode
	switch_to_theatre_mode(gkoka);

	// Remove this collision pair from the checker to avoid 
	// callback spamming ; )
	gkoka->cc->Cancel(g, p);

	// Play sound 
        SoundManager::Singleton()->PlayEffect(6, GAMEOVER);

	// Reset/reposition/clean up
	gkoka->sch->_register(
	 new ResetStageTask(currTime + MAP_RESET_DELAY),
	 new reset_data(gkoka, g, p));
}

void pacman_death_by_smash_callback(GameSprite *pac, Sprite *smasher,
 void *closure)
{
	_shca *ska = CAST(_shca*, closure);

	ska->cc->Cancel(smasher, pac);
	db("Krap!");
} // pacman_death_by_smash_callback

// ActorSuspender / ActorResumer implementations ------------------------
ActorSuspender::result_type
ActorSuspender::operator()(argument_type p) { p.second->suspend(t); }
ActorSuspender::ActorSuspender(timestamp_t _t) : t(_t) { }

ActorResumer::result_type
ActorResumer::operator ()(argument_type p) { p.second->resume(t); }
ActorResumer::ActorResumer(timestamp_t _t) : t(_t) { }


reset_data::reset_data(_gcoca *_gkoka, Sprite *ca, Sprite *stoo) :
	  gkoka(_gkoka)
	, callbacker(ca)
	, stoocker(stoo)
	{ }
reset_data::~reset_data(void) { }

// Theatre mode switcer -------------------------------------------------
void switch_to_theatre_mode(_gcoca *gkoka) {
	register timestamp_t currTime = cs454_2006::getCurrentTime();
	// Pause all actor sprites --
	// Suspend all actor animators.
	std::for_each(gkoka->akmovs->begin(), gkoka->akmovs->end(),
	 ActorSuspender(currTime));

	// Also suspend all the animators
	AnimatorHolder::suspendAllRunning(currTime);

	// Tell input control to ignore some things
	*gkoka->theatre_mode = true;
} // switch_to_theatre_mode

void leave_theatre_mode(_gcoca *gkoka) {
	register timestamp_t currTime = cs454_2006::getCurrentTime();
	// Unpause all actor sprites --
	// Resumer all actor animators.
	std::for_each(gkoka->akmovs->begin(), gkoka->akmovs->end(),
	 ActorResumer(currTime));

	// Resume all animators
	AnimatorHolder::resumeAllExRunning(currTime);

	// Tell input control we are off theatre mode
	*gkoka->theatre_mode = false;
} // leave_theatre_mode


// _shca -- Shmash Callback closure data -- Implementation -----------------
_shca::_shca(
	CollisionChecker *_cc
) :
	cc(_cc)
	{ }
