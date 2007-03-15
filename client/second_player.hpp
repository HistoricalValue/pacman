/* Functions that control the second player. 
 */

#ifndef __second_player_hpp__
#define __second_player_hpp__
#include "client.hpp"

void enableGhostInput(Ghosts &, GameData::io_bools &);
void disableGhostInput(Ghosts &, GameData::io_bools &);

struct GhostPlayerTaskData : public TaskData {
	Ghosts &ghost;
	GameData::io_bools &iob;
	GhostPlayerTaskData(Ghosts &, GameData::io_bools &);
	~GhostPlayerTaskData(void);
}; // struct GhostRevertTaskData

struct GhostPlayerTask : public Task {
	void operator()(TaskData *);
	Task &operator++(void);
	Task &operator+=(timestamp_t);
	GhostPlayerTask(timestamp_t time); ~GhostPlayerTask(void);
}; // struct GhostPlayertTask

#endif // __second_player_hpp__

