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
	Task(t, false) { }

ResetStageTask::result_type
ResetStageTask::operator()(argument_type taskdata) {
	reset_data *rd = DYNCAST(reset_data*, taskdata);
	cs454_2006::nf(!rd, "Task data for stage reset task are "
	 "not reset_data");
	
	// Move all special sprites to initial positions
	std::for_each(
	 rd->gkoka->initpos->begin(),
	 rd->gkoka->initpos->end(),
	 PositionSetter());
} // ResetStageTask()

Task &ResetStageTask::operator ++(void) { return *this; }
Task &ResetStageTask::operator +=(timestamp_t _t) {
	time += _t;
	return *this;
} // ResetStageTask +=

// Destructor
ResetStageTask::~ResetStageTask(void) { }

// Position Setter Implementation ---------------------------------------
PositionSetter::result_type
PositionSetter::operator()(argument_type p) {
	p.first->SetPosition(p.second.x, p.second.y);
} // PositionSetter()
