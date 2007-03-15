#include "second_player.hpp"

struct GhostPlayerTaskData : public TaskData {
  Ghosts &ghost;
  GameData::io_bools &iob;
}; // struct GhostRevertTaskData

struct GhostPlayerTask : public Task {
	void operator()(TaskData *);
	Task &operator++(void);
	Task &operator+=(timestamp_t);
	GhostPlayerTask(timestamp_t time); ~GhostPlayerTask(void);
}; // struct GhostPlayertTask

void enableGhostInput(Ghosts &ghost, GameData::io_bools &iob) {
	static uint8_t ghost_select = 0;
	disableGhostInput(ghost, iob);
	switch (ghost_select) {
		case 0: ghost.player2 = ghost.stalker; break;
		case 1: ghost.player2 = ghost.kieken; break;
		case 2: ghost.player2 = ghost.random; break;
		case 3: ghost.player2 = ghost.retard; break;
		default : nf(-1, "Illegal program state"); break;
	}
	ghost_select = ghost_select > 2 ? 0 : ghost_select + 1;
	ghost.player2->setControlled(true);
	iob.second_player = true;
}// enableGhostInput

void disableGhostInput(Ghosts &ghost, GameData::io_bools &iob) {
	if (ghost.player2)
		ghost.player2->setControlled(false);
	iob.second_player = false;
}// disableGhostInput

/*
Task &GhostPlayerTask:: public Task {
	void operator()(TaskData *);
	Task &operator++(void);
	Task &operator+=(timestamp_t);
	GhostRevertTask(timestamp_t time); ~GhostRevertTask(void);
}; // struct GhostRevertTask

*/

void GhostPlayerTask::operator()(TaskData *tsk){
  enableGhostInput(
		   dynamic_cast<GhostPlayerTaskData*>(tsk)->ghost, 
		   dynamic_cast<GhostPlayerTaskData*>(tsk)->iob
		   );
}

Task &GhostPlayerTask::operator++(void){
  time+=10000;
}

Task &GhostPlayerTask::operator+=(timestamp_t _t){
  time+=_t;
}

GhostPlayerTask::GhostPlayerTask(timestamp_t time) :
  Task(time, false) { }

GhostPlayerTask::~GhostPlayerTask(){ }
