#include "death_pacman.hpp"
#include "SoundManager.hpp"
#include "AnimatorHolder.hpp"
#include "reset.hpp"
#include "config.h"
#include "ObstacleSprite.hpp"

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
struct switch_to_theatre_mode_task : public Task {
	void operator ()(taskdata_t);
	switch_to_theatre_mode_task &operator++(void);
	switch_to_theatre_mode_task(timestamp_t);
	~switch_to_theatre_mode_task(void);
}; // struct switch_to_theatre_mode_task
struct switch_to_theatre_mode_task_data : public TaskData {
	_gcoca *gkoka;
	switch_to_theatre_mode_task_data(_gcoca *gkoka);
	~switch_to_theatre_mode_task_data(void);
};

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
	if(gkoka->gs->LoseLife())
	  gkoka->gs->ShowGameOver();
}

void pacman_death_by_smash_callback(GameSprite *pac, Sprite *smasher,
 void *closure)
{
	if (!pac->IsSmashed()) {
		ObstacleSprite *smasha = DYNCAST(ObstacleSprite*, smasher);
		nf(!smasha, "Smasher is not an obstacle!");
		_shca *ska = CAST(_shca*, closure);
		
		// Same as in death_by_ghost
		register timestamp_t timesand =
		 cs454_2006::getCurrentTime();
		
		// Go into theatre mode.
		// ---
		// It is actually safer to register a task for the same
		// time as now (so it will be run in the same gaim loop
		// iteration) so that all structure modifications happen
		// after iterations over them are finished.
		ska->gkoka->sch->_register(
		 new switch_to_theatre_mode_task(timesand),
		 new switch_to_theatre_mode_task_data(ska->gkoka)
		);
		//switch_to_theatre_mode(ska->gkoka);
		
		// collision callback spamming will be prevented
		// with the IsSmashed state
		// --- But ---
		// whether we like it or not those two sprites must be
		// canceled from the collision checker because the 
		// map-restore task will reregister them
		//ska->gkoka->cc->Cancel(smasher, pac);
		// --- But ---
		// It is not necessary after all since the CC checks
		// to make sure not the same pair is inserted evah ; )

		// Play sound
		// TODO add sound
	
		// reset/reposition/clean up
		SoundManager::Singleton()->PlayEffect(6, WALL);
		ska->gkoka->sch->_register(
		 new ResetStageTask(timesand + MAP_RESET_DELAY),
		 new reset_data(ska->gkoka, smasher, pac));
		if(ska->gkoka->gs->LoseLife())
		  ska->gkoka->gs->ShowGameOver();
	}
} // pacman_death_by_smash_callback
void switch_to_theatre_mode_task::operator ()(taskdata_t _data) {
	switch_to_theatre_mode_task_data* data = DYNCAST(
	 switch_to_theatre_mode_task_data*, _data);
	nf(!data, "Data passed to switch to theatre mode task is not "
	 "switch_to_theatre_mode_task_data");
	switch_to_theatre_mode(data->gkoka);
} // switch_to_theatre_mode_task()

switch_to_theatre_mode_task &switch_to_theatre_mode_task::operator ++(void){
	return *this;
} // switch_to_theatre_mode_task++

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

// To theater mode - task -----------------
switch_to_theatre_mode_task_data::switch_to_theatre_mode_task_data(
 _gcoca *_gkoka) :
 	  gkoka(_gkoka)
	{ }
switch_to_theatre_mode_task_data::~switch_to_theatre_mode_task_data(void){}

switch_to_theatre_mode_task::switch_to_theatre_mode_task(timestamp_t _t) :
	  Task(_t, false)
	{ }
switch_to_theatre_mode_task::~switch_to_theatre_mode_task(void) { }

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
	//std::for_each(gkoka->akmovs->begin(), gkoka->akmovs->end(),
	// ActorResumer(currTime));

	// Resume all animators
	AnimatorHolder::resumeAllExRunning(currTime);

	// Tell input control we are off theatre mode
	*gkoka->theatre_mode = false;
} // leave_theatre_mode


// _shca -- Shmash Callback closure data -- Implementation -----------------
_shca::_shca( _gcoca *_gkoka) : gkoka(_gkoka) { }
