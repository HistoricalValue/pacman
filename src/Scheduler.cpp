#include "Scheduler.hpp"
#include <algorithm>

struct Task {
	bool operator==(Task const&) const;
	bool operator==(Task const&);
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

	}
} // Scheduler::_register
