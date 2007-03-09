#include "ActorMovement.hpp"
using namespace cs454_2006;

// Suspends given animator
struct ActorMovement::SuspendFunctor {
	void operator() (ActorMovement::AnimatorPair*) const;
	SuspendFunctor(timestamp_t);
	private :
	timestamp_t t;
};

// Struct that help manipulate both animation animators at once
struct ActorMovement::AnimatorPair {
	AnimatorPair(char const*,MovingAnimator*,FrameRangeAnimator*);
	void Suspend(timestamp_t);
	void Resume(timestamp_t);
	bool ShouldProgress(timestamp_t);
	bool EnsureProgressable(int, timestamp_t);
	void Progress(timestamp_t);
	// Performs all operations which have to be sure that there will be
	// no collision in order to take place.
	void CatchUp(timestamp_t);
	operator Animator *(void);
	MovingAnimator *getMV(void);
	FrameRangeAnimator *getFR(void);
//	Animator *operator*(void);
	private :
	MovingAnimator *mv;
	FrameRangeAnimator *fr;
	const char *direction;
}; // struct AnimatorPair

// Delay setter
struct ActorMovement::DelaySetter :
 public std::unary_function<AnimatorPair*, void>
{
	void operator()(AnimatorPair*);
	DelaySetter(delay_t);
	private :
	delay_t d;
}; // struct DelaySetter

// Constructor
ActorMovement::ActorMovement(GameSprite *_actor,
 std::vector<MovingAnimator*> const &_mv,
 std::vector<FrameRangeAnimator*> const &_fr,
 amc_t &_amc,
 timestamp_t t) :
 actor(_actor), w2g(static_cast<AnimatorPair*>(0)),
 running(w2g), w2g_collided(false), amc(_amc)
{
	assert(_mv.size() >= 4 && _fr.size() >= 4);
	SuspendFunctor sfunctor(t);
	animators.push_back(
	 new AnimatorPair("UP",_mv.at(UP), _fr.at(UP)));
	animators.push_back(
	 new AnimatorPair("RIGHT",_mv.at(RIGHT), _fr.at(RIGHT)));
	animators.push_back(
	 new AnimatorPair("DOWN",_mv.at(DOWN), _fr.at(DOWN)));
	animators.push_back(
	 new AnimatorPair("LEFT",_mv.at(LEFT), _fr.at(LEFT)));
	std::for_each(animators.begin(), animators.end(), sfunctor);
} // constructor

void ActorMovement::pressed(enum move_t direction, timestamp_t currTime) {
	if (direction != NOWHERE && running != animators.at(direction)) {
		if (w2g) w2g->Suspend(currTime);
		(w2g = animators.at(direction))->Resume(currTime);
	}
} // pressed

void ActorMovement::released(enum move_t direction, timestamp_t currTime) {
	if (direction != NOWHERE && w2g == animators.at(direction) ) {
		w2g->Suspend(currTime);
		w2g = static_cast<AnimatorPair*>(0);
	}
} // released

void ActorMovement::progress(timestamp_t currTime) {
	// if no animator is running yet, try moving where user w2g
	if (!running){running = w2g; w2g = static_cast<AnimatorPair*>(0);}
	if (running) // if going somewhere
	while (running->ShouldProgress(currTime) &&
	 CAST(Animator*, (*running))->isRunning())
	{
		if (w2g) { // if trying to go somewhere else
			nf(w2g->EnsureProgressable(1,currTime)!=true, "");
			nf(w2g->ShouldProgress(currTime)!=true, "");
			w2g->Progress(currTime); // Progress (1 step)
			w2g_collided = false; // check done in cc->Check()
			amc(*w2g); // check
			// now w2g_collided should hold the correct value
		}
		if (w2g_collided || !w2g) {
			// there is an obst to where the actor w2g, so
			// normal movement must continue
			// - OR -
			// the actor does not want to change course, so
			// normal movement must continue
			running->Progress(currTime);
		} else {
			// the actor wants to change course
			// - AND -
			// the path to where it wants to go is free
			running->Suspend(currTime);
			(running = w2g);
			w2g = NULL;
		}
		running->CatchUp(currTime); // do collision-dependant ops
		amc(*running);
	}
} // progress

void ActorMovement::collided(GameSprite *_actor) {
	if (_actor->getID() == actor->getID()) // it's our actor
		w2g_collided = true;
} // collided

// Suspend Functor
void ActorMovement::SuspendFunctor::operator() (ActorMovement::AnimatorPair *a) const
	{ a->Suspend(t); }
ActorMovement::SuspendFunctor::SuspendFunctor(timestamp_t _t) : t(_t) { }

// AnimatorPair
// constructor
ActorMovement::AnimatorPair::AnimatorPair( char const *_d,
 MovingAnimator *_mv, FrameRangeAnimator *_fr) : mv(_mv), fr(_fr),
 direction(_d){ }

void ActorMovement::AnimatorPair::Suspend(timestamp_t currTime) {
	mv->Suspend(currTime);
	fr->Suspend(currTime);
}

void ActorMovement::AnimatorPair::Resume(timestamp_t currTime) {
	mv->Resume(currTime);
	fr->Resume(currTime);
}

bool ActorMovement::AnimatorPair::ShouldProgress(timestamp_t currTime) {
	return mv->ShouldProgress(currTime);
}

bool ActorMovement::AnimatorPair::EnsureProgressable(int s, timestamp_t t) {
	fr->EnsureProgressable(s, t); // unable to progress fr is not lethal
	return mv->EnsureProgressable(s, t);
}

void ActorMovement::AnimatorPair::Progress(timestamp_t currTime) {
	mv->Progress(currTime);
}

// Performs all operations which have to be sure that there will be
// no collision in order to take place.
void ActorMovement::AnimatorPair::CatchUp(timestamp_t currTime) {
	fr->Progress(currTime);
}

ActorMovement::AnimatorPair::operator Animator *(void) { return mv; }

// Get Animators
MovingAnimator*
ActorMovement::getMovingAnimator(void) { return running->getMV(); }
FrameRangeAnimator*
ActorMovement::getFrameRangeAnimator(void) { return running->getFR(); }
MovingAnimator*
ActorMovement::AnimatorPair::getMV(void) { return mv; }
FrameRangeAnimator*
ActorMovement::AnimatorPair::getFR(void) { return fr; }

enum ActorMovement::move_t ActorMovement::getLastMove(void) const {
	int i;
	for (i = UP; i < 4; ++i)
		if (animators[i] == running)
			break;
	return i == 4 ? NOWHERE : static_cast<enum move_t>(i);
} // getLastMove

void ActorMovement::setDelay(delay_t d) {
	std::for_each(animators.begin(), animators.end(),
	 DelaySetter(d));
} // setDelay

ActorMovement::DelaySetter::DelaySetter(delay_t _d) : d(_d) { }

void ActorMovement::DelaySetter::operator()(AnimatorPair *p) {
	p->getMV()->getAnimation()->SetDelay(d);
//	p->getFR()->GetAnimation()->SetDelay(d);
} // ActorMovement::DelaySetter::()

void ActorMovement::suspend(timestamp_t t) {
	if (w2g) if (CAST(Animator*, *w2g)->isRunning()) w2g->Suspend(t);
	if (running)
		running->Suspend(t);
} // suspend

void ActorMovement::resume(timestamp_t t) {
	if (running)
		running->Resume(t);
} // resume

void ActorMovement::reset(void) {
	  w2g = static_cast<AnimatorPair*>(0)
 	, running = w2g
	, w2g_collided = false;
} // reset
