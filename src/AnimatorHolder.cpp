#include "AnimatorHolder.hpp"
using namespace cs454_2006;

std::list<Animator*> AnimatorHolder::running;
std::list<Animator*> AnimatorHolder::suspended;
amc_t const* AnimatorHolder::amc;

// ProgressFunctor members    -------------
void AnimatorHolder::ProgressFunctor::operator () (Animator* a) const {
	while (a->ShouldProgress(t)) {
		a->Progress(t);
		// make all necessary checks after every move
		if (amc)
			(*amc)(a);
	}
} // operator ()
 // Constructor
AnimatorHolder::ProgressFunctor::ProgressFunctor(timestamp_t _t) : t(_t) { }
// End ProgressFunctor members  -------------

// TimeshiftFunctor members     -------------
void AnimatorHolder::TimeshiftFunctor::operator () (Animator* a) const {
	a->TimeShift(t);
} // operator ()
 // Constructor
AnimatorHolder::TimeshiftFunctor::TimeshiftFunctor(timestamp_t _t): t(_t){ }
// End TimeshiftFunctor members -------------


void AnimatorHolder::Register (Animator* a) { suspended.push_back(a); }
void AnimatorHolder::Cancel (Animator* a) { suspended.remove(a); }
void AnimatorHolder::MarkAsRunning (Animator* a)
	{ suspended.remove(a); running.push_back(a); }
void AnimatorHolder::MarkAsSuspended (Animator* a)
	{ running.remove(a); suspended.push_back(a); }
void AnimatorHolder::Progress (timestamp_t currTime) {
    std::for_each(
	running.begin(), running.end(), ProgressFunctor(currTime)
    ); 
}
void AnimatorHolder::TimeShift (timestamp_t currTime) {
	if (running.size())
		std::for_each(
		 running.begin(),
		 running.end(),
		 TimeshiftFunctor(currTime)
		);
	if (suspended.size())
		std::for_each(
		 suspended.begin(),
		 suspended.end(),
		 TimeshiftFunctor(currTime)
		);
}

amc_t const* AnimatorHolder::getAfterMoveCall(void) { return amc; }

void AnimatorHolder::setAfterMoveCall(amc_t const* _amc) { amc = _amc; }

std::list<Animator*> AnimatorHolder::getRunning(void) {
	return running;
} // getRunningAnimators
