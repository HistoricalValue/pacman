/* Reset the stage to be playable again.
 * 
 */

#ifndef __rest_hpp__
#define __rest_hpp__

#include "Scheduler.hpp"
#include "_ghost.hpp"
#include "death_pacman.hpp"

struct reset_data : public TaskData {
	_gcoca *gkoka;
	// sprites to re-register for collision checking
	Sprite *callbacker, *stoocker; 
	reset_data(_gcoca*, Sprite *ca, Sprite *stoo); ~reset_data(void);
};


#if 0
The stage reseter actually has to perform two operations instead of one:
First it ought to reposition the special sprites in the map and, second,
after a certain amount of time passes, if has to restart the animators so 
that the special sprites get back in motion.

To achieve this in a simpler way and to avoid adding more classes to extend
::Task , this same task will at first behave as a recurring task and the
second time that it will be executed, it will perform the second task and
change its state to not recurring.
#endif
class ResetStageTask : public Task {
	public :
	void operator()(taskdata_t);
	Task &operator++(void);
	ResetStageTask(timestamp_t); virtual ~ResetStageTask(void);
	private :
	enum mode_t {repos, restart} mode;
}; // class ResetStageTask
extern void reset_stage(reset_data*);
#endif // __rest_hpp__

