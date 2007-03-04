/* Reset the stage to be playable again.
 * 
 */

#ifndef __rest_hpp__
#define __rest_hpp__

#include "Scheduler.hpp"
#include "ghost.hpp"

struct reset_data : public TaskData {
	_gcoca *gkoka;
	reset_data(_gcoca*); ~reset_data(void);
};

class ResetStageTask : public Task {
	public :
	void operator()(taskdata_t);
	Task &operator++(void);
	Task &operator+=(timestamp_t);
	ResetStageTask(timestamp_t); virtual ~ResetStageTask(void);
}; // class ResetStageTask
extern void reset_stage(reset_data*);
#endif // __rest_hpp__

