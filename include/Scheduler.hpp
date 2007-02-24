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

typedef class Task *task_t;
typedef struct TaskData *taskdata_t;

class Scheduler {
	public :
	typedef enum {DONE, PENDING} status_t;
	void _register(task_t const&, taskdata_t const&);
	status_t track(task_t const&);
	bool cancel(task_t const&);
	void check(timestamp_t currTime);
	Scheduler(timestamp_t starting_time);
	~Scheduler(void);
	private :
	struct TaskExecutor;
	std::map<task_t, taskdata_t> tasks;
	std::list<task_t> times;
	TaskExecutor *executor;
}; // class Scheduler

class Task {
	public :
	virtual bool operator==(Task const*) const = 0;
	virtual void operator()(taskdata_t) const = 0;
	virtual Task&operator++(void) = 0;
	Task(timestamp_t diff, bool recurring); virtual ~Task(void);
	timestamp_t getTime(void) const;
	bool isRecurring(void) const;
	private :
	timestamp_t time;
	bool recurring;
}; // class Task
struct TaskData { };

#endif // __Scheduler_hpp__
