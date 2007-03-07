#include "Scheduler.hpp"
#include "commons.hpp"
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
	if (status == suspended) {
		db("WARNING: Running a suspended Scheduler");
	} else {
		executor->setCurrentTime(currTime);
		// Check and run what tasks is needed
		std::for_each(times.begin(), times.end(), *executor);
		// Clean up (remove) dirty tasks
		times.remove_if(isdirty);
	}
} // Scheduler::check

bool Scheduler::cancel(task_t const &t) {
	tasks.erase(tasks.find(t));
	times.remove(t);

	return true;
} // Scheduler::cancel

void Scheduler::suspend(timestamp_t currTime) {
	if (status == suspended) {
		db("WARNING: Suspended a suspended scheduler.");
	} else {
		suspendTime = currTime;
		status = suspended;
	}
} // suspend()

void Scheduler::resume(timestamp_t t) {
	if (status == running) {
		db("WARNING: Resuming a running scheduler.");
	} else {
		timestamp_t d = timestamp_diff(t, suspendTime);
		std::for_each(times.begin(), times.end(), taskShifter = d);
		status = running;
	}
} // resume()

// Task Executor Implementation --------------------------------------------
void Scheduler::TaskExecutor::operator()(task_t t) const {
	if (currTime >= t->getTime()) { // should run task
		(*t)(sch->tasks[t]); // run it
		// if task is not recurring, mark task for removal
		if (!t->isRecurring())
			t->makeDirty();
		else
			// Advance task's execution time and leave
			// registered
			++(*t);
	}
} // TaskExecutor::()

void Scheduler::TaskExecutor::setCurrentTime(timestamp_t _currTime) {
	currTime = _currTime;
} // TaskExecutor::setCurrentTime()

// Task Implementation -----------------------------------------------------
timestamp_t Task::getTime(void) const { return time; }
bool Task::isRecurring(void) const { return recurring; }
void Task::makeDirty(void) { dirty = true; }
bool Task::isDirty(void) const { return dirty; }
Task &Task::operator +=(timestamp_t off) { time += off; return *this; }

// IsDirtyPredicate Implementation -----------------------------------------
bool Scheduler::IsDirtyPredicate::operator()(Task *t) {
	return t->isDirty();
} // IsDirtyPredicate::()

// TaskShifter implementation ----------------------------------------------
Scheduler::TaskShifter
&Scheduler::TaskShifter::operator=(timestamp_t _t) { t = _t; return *this; }
Scheduler::TaskShifter::result_type
Scheduler::TaskShifter::operator()(argument_type task) {
	(*task) += t; // time shift each task by time diff "t"
} // TaskShifter::()

// Constructors
Scheduler::Scheduler(timestamp_t _startingTime) :
	  status(running)
	, executor(new TaskExecutor(_startingTime, this))
	, suspendTime(0)
	{ }
Scheduler::TaskExecutor::TaskExecutor(timestamp_t _currTime,Scheduler*_sch):
	currTime(_currTime),
	sch(_sch) { }
Task::Task(timestamp_t _time, bool _recurring) :
	time(_time),
	recurring(_recurring),
	dirty(false) { }
Scheduler::IsDirtyPredicate::IsDirtyPredicate(void) { }

// Destructors
Scheduler::~Scheduler(void) {
	std::map<task_t, taskdata_t>::iterator ite;
	for (ite = tasks.begin(); ite != tasks.end(); ite++) {
		delete ite->first;
		delete ite->second;
	}
	delete executor;
}
Task::~Task(void) { }
TaskData::~TaskData(void) {}
Scheduler::IsDirtyPredicate::~IsDirtyPredicate(void) { }
