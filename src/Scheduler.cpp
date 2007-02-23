#include "Scheduler.hpp"
#include <algorithm>

struct TaskData { };

struct Task {
	virtual bool operator==(Task const&) const;
	virtual bool operator==(Task const&);
	virtual void operator()(TaskData&);
	Task(void);
	virtual ~Task(void);
};

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
	
} // Scheduler::check
