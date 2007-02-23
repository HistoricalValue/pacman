/* Scheduler.hpp
 *
 * Executes tasks on a scheduled time.
 * Tasks can be registered and their status tracked.
 */

#ifndef __Scheduler_hpp__
#define __Scheduler_hpp__

#include <map>
#include <list>
#include "Animator.hpp" // for timestamp_t

typedef struct Task *task_t;
typedef struct TaskData *taskdata_t;

class Scheduler {
	public :
	typedef enum {DONE, PENDING} status_t;
	void _register(task_t const&, taskdata_t const&);
	status_t track(task_t const&);
	bool cancel(task_t const&);
	void check(timestamp_t currTime);
	Scheduler(void);
	~Scheduler(void);
	private :
	std::map<task_t, taskdata_t> tasks;
	std::list<task_t> times;
}; // class Scheduler

#endif // __Scheduler_hpp__
