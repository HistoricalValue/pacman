#include "Animator.hpp"
#include "AnimatorHolder.hpp"
#include "commons.hpp"

void Animator::Stop (void) {
	if (!HasFinished()) {
		state = ANIMATOR_STOPPED;
		NotifyStopped();
	}
}

void Animator::NotifyStopped (void) {
	if (onFinish) {
		(*onFinish)(this, finishClosure);
	}
}

bool Animator::HasFinished (void) const {
	return state == ANIMATOR_FINISHED;
}

void Animator::TimeShift (timestamp_t offset) {
	lastTime += offset;
}
	
// Constructor
Animator::Animator (bool __register) :
 lastTime(0), suspendedTime(0), state(ANIMATOR_FINISHED), exState(state),
 onFinish((FinishCallback) 0), finishClosure((void*) 0),
 _register(__register)
{
	if (_register)
		AnimatorHolder::Register(this);
}

void Animator::SetOnFinish (FinishCallback f, void *c = (void*) 0){
	onFinish = f; finishClosure = c;
}

Animator::~Animator(void) {
	AnimatorHolder::Cancel(this);
}

timestamp_t timestamp_diff(timestamp_t a, timestamp_t b) {
	return b > a ? 0 : a - b;
}

void Animator::Suspend(timestamp_t currTime) {
	if (state != ANIMATOR_STOPPED) { // can be suspended once
		suspendedTime = currTime;
		exState = state;
		state = ANIMATOR_STOPPED;
		db("here");
		if (_register) // if registered with the holder
			AnimatorHolder::MarkAsSuspended(this);
	} else
		db("Warning: suspending a supsended animator");
} // Suspend

void Animator::Resume(timestamp_t currTime) {
	if (state == ANIMATOR_STOPPED) { // only act if animator is suspened
		TimeShift(currTime - suspendedTime);
		state = exState;
		if (_register) // if registered with the Holder
			AnimatorHolder::MarkAsRunning(this);
	} else
		db("Waning: resuming a non-suspended animator");
} // Resume
