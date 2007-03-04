#include "death_ghost.hpp"
#include "SoundManager.hpp"
#include "AnimatorHolder.hpp"
#include "reset.hpp"
#include "config.h"

struct ActorSuspender : public std::unary_function<
 std::pair<GameSprite* const, ActorMovement*>, void> {
	 result_type operator()(argument_type);
	 ActorSuspender(timestamp_t);
	 private :
	 timestamp_t t;
}; // struct ActorSuspender

void ghost_death_callback(Ghost *g, GameSprite *p, _gcoca *gkoka) {
	// Super FX mode! Pause all ghosts and pacman
	
	register timestamp_t currTime = cs454_2006::getCurrentTime();
	// Pause all actor sprites --
	// Suspend all actor animators.
	std::for_each(gkoka->akmovs->begin(), gkoka->akmovs->end(),
	 ActorSuspender(currTime));

	// Also suspend all the animators
	AnimatorHolder::suspendAllRunning(currTime);

	// Remove this collision pair from the checker to avoid 
	// callback spamming ; )
	gkoka->cc->Cancel(g, p);

	// Play sound 
        SoundManager::Singleton()->PlayEffect(6, GAMEOVER);
	
	// Reset/reposition/clean up
	gkoka->sch->_register(
	 new ResetStageTask(currTime + MAP_RESET_DELAY),
	 new reset_data(gkoka));
}

ActorSuspender::result_type
ActorSuspender::operator()(argument_type p) {
	p.second->suspend(t);
} // ActorSuspender()

ActorSuspender::ActorSuspender(timestamp_t _t) : t(_t) { }

reset_data::reset_data(_gcoca *_gkoka) : gkoka(_gkoka) { }
reset_data::~reset_data(void) { }
