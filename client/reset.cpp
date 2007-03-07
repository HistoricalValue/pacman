#include "reset.hpp"

// Implementation headers
#include "commons.hpp"

// Sets ths given sprite to the position the Rect indicates 
struct PositionSetter : public std::unary_function<std::pair<GameSprite * const,
 SDL_Rect>&, void> {
	 result_type operator()(argument_type);
 }; // struct InitPosSetter

// ResetStageTask Implementation ---------------------------------------
// Constructor
ResetStageTask::ResetStageTask(timestamp_t t) :
	  Task(t, true)
	, mode(repos)
	{ }

ResetStageTask::result_type
ResetStageTask::operator()(argument_type taskdata) {
	reset_data *rd = DYNCAST(reset_data*, taskdata);
	nf(!rd, "Task data for stage reset task are "
	 "not reset_data");
	
	switch (mode) {
		case repos : // reposition sprites
			// Move all special sprites to initial positions
			std::for_each(
			 rd->gkoka->initpos->begin(),
			 rd->gkoka->initpos->end(),
			 PositionSetter());
			// we should be recurring at this point
			nf(!recurring, "Should be dirty");
			break;
		case restart : // restart animators and such
			// Leave theatre mode
			leave_theatre_mode(rd->gkoka);
			// Clean up any other change the death callback did
			rd->gkoka->cc->Register(
			 rd->callbacker,
			 rd->stoocker);
			// Make us no more recurring
			recurring = false;
			break;
		default :
			nf(-1, "Wrong program state");
	}
} // ResetStageTask()

// Switch to restarter mode
Task &ResetStageTask::operator ++(void) {
	// Set the next execution time to be when things should get
	// moving again
	time += RESTARTING_DELAY;
	// Change execution mode
	mode = restart;
	
	return *this;
} // ResetStageTask++

// Destructor
ResetStageTask::~ResetStageTask(void) { }

// Position Setter Implementation ---------------------------------------
PositionSetter::result_type
PositionSetter::operator()(argument_type p) {
	p.first->SetPosition(p.second.x, p.second.y);
} // PositionSetter()
