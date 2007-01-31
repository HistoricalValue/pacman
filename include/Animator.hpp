#ifndef _ANIMATOR_HPP_
#define _ANIMATOR_HPP_

typedef unsigned long timestamp_t;
enum animatorstate_t {
	ANIMATOR_FINISHED	= 0,
	ANIMATOR_RUNNING	= 1,
	ANIMATOR_STOPPED	= 2
};

timestamp_t timestamp_diff(timestamp_t, timestamp_t);

class Animator {
public:
	typedef void (*FinishCallback)(Animator*,void*);
protected:
	timestamp_t		lastTime, suspendedTime;
	animatorstate_t		state, exState;
	FinishCallback		onFinish;
	void*			finishClosure;
	void NotifyStopped (void);
	bool _register;
public:
	void Stop (void);
	bool HasFinished (void) const ;
	virtual void Suspend(timestamp_t currTime);
	virtual void Resume(timestamp_t currTime);
	virtual void TimeShift (timestamp_t offset);
	virtual void Progress (timestamp_t currTime) = 0;
	virtual bool ShouldProgress(timestamp_t currTime) = 0;
	void SetOnFinish (FinishCallback, void*);
	Animator (bool _register = true);
	virtual ~Animator(void);
};

#endif
