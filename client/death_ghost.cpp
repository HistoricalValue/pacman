#include "death_ghost.hpp"
#include "SoundManager.hpp"
#include "AnimatorHolder.hpp"
#include "reset.hpp"

struct ActorSuspender : public std::unary_function<
 std::pair<GameSprite* const, ActorMovement*>, void> {
	 result_type operator()(argument_type);
	 ActorSuspender(timestamp_t);
	 private :
	 timestamp_t t;
}; // struct ActorSuspender

void ghost_death_callback(Ghost *g, GameSprite *p, _gcoca *gkoka) {
	// Super FX mode! Pause all ghosts and pacman
        SoundManager::Singleton()->PlayEffect(6, GAMEOVER);
	timestamp_t currTime = cs454_2006::getCurrentTime();
	// Pause all actor sprites --
	// Suspend all actor animators.
	std::for_each(gkoka->akmovs->begin(), gkoka->akmovs->end(),
	 ActorSuspender(currTime));

	// Also suspend all the animators
	AnimatorHolder::suspendAllRunning(currTime);

	// Remove this collision pair from the checker to avoid 
	// callback spamming ; )
	gkoka->cc->Cancel(g, p);

	// Play sound in the future
	// TODO
	
	// Wait for sound
	// TODO
	cs454_2006::delay(5000);

	// Reset/reposition/clean up
	reset_stage(new reset_data());
}

ActorSuspender::result_type
ActorSuspender::operator()(argument_type p) {
	p.second->suspend(t);
} // ActorSuspender()

ActorSuspender::ActorSuspender(timestamp_t _t) : t(_t) { }
