#include "AnimatorHolder.hpp"
using namespace cs454_2006;

std::list<Animator*>
	AnimatorHolder::running,
	AnimatorHolder::suspended,
	AnimatorHolder::x_running;
amc_t const *AnimatorHolder::amc;
AnimatorHolder::_susres AnimatorHolder::susres(running, x_running);

// ProgressFunctor members    -------------
void AnimatorHolder::ProgressFunctor::operator () (Animator *a) const {
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
void AnimatorHolder::TimeshiftFunctor::operator () (Animator *a) const {
	a->TimeShift(t);
} // operator ()
 // Constructor
AnimatorHolder::TimeshiftFunctor::TimeshiftFunctor(timestamp_t _t): t(_t){ }
// End TimeshiftFunctor members -------------


void AnimatorHolder::Register (Animator *a) { suspended.push_back(a); }
void AnimatorHolder::Cancel (Animator *a) { suspended.remove(a); }
void AnimatorHolder::MarkAsRunning (Animator *a)
	{ suspended.remove(a); running.push_back(a); }
void AnimatorHolder::MarkAsSuspended (Animator *a)
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

amc_t const *AnimatorHolder::getAfterMoveCall(void) { return amc; }

void AnimatorHolder::setAfterMoveCall(amc_t const *_amc) { amc = _amc; }

std::list<Animator*> AnimatorHolder::getRunning(void) {
	return running;
} // getRunning

std::list<Animator*> AnimatorHolder::getSuspended(void) {
	return suspended;
} // getSuspended

void AnimatorHolder::suspendAllRunning(timestamp_t currTime) {
	std::for_each(running.begin(), running.end(),
	 susres[susres.suspend] = currTime);
} // suspendAllRunning

void AnimatorHolder::resumeAllExRunning(timestamp_t currTime) {
	std::for_each(x_running.begin(), x_running.end(),
	 susres[susres.resume] = currTime);
} // resumeAllExRunning

// Suspender/Resumer Implementation ------------------------------------
AnimatorHolder::_susres::_susres(std::list<Animator*> &_r,
 std::list<Animator*> &_x) : r(_r), x(_x) { }

AnimatorHolder::_susres &AnimatorHolder::_susres::operator[](enum mode _m) {
	m = _m;
	return *this;
} // susres[]

AnimatorHolder::_susres &AnimatorHolder::_susres::operator=(timestamp_t T) {
	t = T;
	return *this;
} // susres =

AnimatorHolder::_susres::result_type
AnimatorHolder::_susres::operator()(argument_type animator) {
	switch (m) {
		case suspend :
			x.push_back(animator);
			animator->Suspend(t);
			break;
		case resume :
			x.remove(animator);
			animator->Resume(t);
			break;
	}
} // susres()
// -----------------------------------------------------------------------
