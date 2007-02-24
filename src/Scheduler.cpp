#include "Scheduler.hpp"
#include <algorithm>

// Checks for each task if it should be executed and executes it if it
// should.
struct Scheduler::TaskExecutor : public std::unary_function<task_t, void> {
	void operator()(task_t) const;
	void setCurrentTime(timestamp_t);
	TaskExecutor(timestamp_t currTime, Scheduler *);
	private :
	timestamp_t currTime;
	Scheduler *sch;
}; // struct TaskExecutor

// Scheduler Implementation ------------------------------------------------
void Scheduler::_register(task_t const &t, taskdata_t const &d) {
	// Make sure task is not registered.
	// (Comparisons are made between pointers and not class IDs so that
	// the same event (even carried out on the same time) can be
	// registered more than once but the same instance of task
	// cannot be registered twice).
	if (std::find_if(times.begin(), times.end(), std::bind1st(
	 std::equal_to<task_t>(), t)) == times.end())
	{
		// Given task is not register, so register it.
		tasks[t] = d;
		times.push_back(t);
	}
} // Scheduler::_register

void Scheduler::check(timestamp_t currTime) {
	// Calculate how much time is past from last time (check was run)
	executor->setCurrentTime(currTime);
	// Check and run what tasks is needed
	std::for_each(times.begin(), times.end(), *executor);
} // Scheduler::check

bool Scheduler::cancel(task_t const &t) {
	tasks.erase(tasks.find(t));
	times.remove(t);

	return true;
} // Scheduler::cancel

// Task Executor Implementation --------------------------------------------
void Scheduler::TaskExecutor::operator()(task_t t) const {
	if (t->getTime() >= currTime) { // should run task
		(*t)(sch->tasks[t]);
		// if task is no reoccuring, remove from the queue
		if (!t->isRecurring())
			sch->cancel(t);
		else
			// Advance task's execution time and leave
			// registered
			++(*t);
	}
} // TaskExecutor::()

void Scheduler::TaskExecutor::setCurrentTime(timestamp_t _currTime) {
	currTime = _currTime;
}

// Task Implementation -----------------------------------------------------
timestamp_t Task::getTime(void) const { return time; }
bool Task::isRecurring(void) const { return recurring; }


// Constructors
Scheduler::Scheduler(timestamp_t _startingTime) :
	executor(new TaskExecutor(_startingTime, this)) { }
Scheduler::TaskExecutor::TaskExecutor(timestamp_t _currTime,Scheduler*_sch):
	currTime(_currTime),
	sch(_sch) { }

// Destructors
Scheduler::~Scheduler(void) {
	std::map<task_t, taskdata_t>::iterator ite;
	for (ite = tasks.begin(); ite != tasks.end(); ite++) {
		delete ite->first;
		delete ite->second;
	}
	delete executor;
}
