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
	void suspend(timestamp_t currTime);
	void resume(timestamp_t currTime);
	void timeshift(timestamp_t diff);
	Scheduler(timestamp_t starting_time);
	~Scheduler(void);
	private :
	enum _status_t {suspended, running} status;
	struct IsDirtyPredicate : public std::unary_function<Task*,bool> {
		bool operator()(Task *);
		IsDirtyPredicate(void); ~IsDirtyPredicate(void);
	}; // struct IsDirtyPredicate
	struct TaskShifter : public std::unary_function<Task*, void> {
		result_type operator()(argument_type);
		TaskShifter &operator=(timestamp_t);
		private :
		timestamp_t t;
	}; // struct TaskShifter
	struct TaskExecutor;
	std::map<task_t, taskdata_t> tasks;
	std::list<task_t> times;
	TaskExecutor *executor;
	IsDirtyPredicate isdirty;
	timestamp_t suspendTime;
	TaskShifter taskShifter;
}; // class Scheduler

class Task : public std::unary_function<taskdata_t, void> {
	public :
	virtual void operator()(taskdata_t) = 0;
	virtual Task &operator++(void) = 0;
	Task &operator+=(timestamp_t);
	Task(timestamp_t time, bool recurring); virtual ~Task(void);
	timestamp_t getTime(void) const;
	bool isDirty(void) const;
	void makeDirty(void);
	bool isRecurring(void) const;
	protected :
	timestamp_t time;
	bool recurring, dirty;
}; // class Task
struct TaskData { virtual ~TaskData(); };

#endif // __Scheduler_hpp__
