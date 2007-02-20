#include "CollisionChecker.hpp"
#include "MovingAnimator.hpp"
#include "AnimatorHolder.hpp"
#include "commons.hpp"
using namespace cs454_2006;

void MovingAnimator::Progress (timestamp_t currTime) {
	// Recursion - a really bad idea
	timestamp_t diff = timestamp_diff(currTime, lastTime);
	delay_t delay = anim->GetDelay();
	assert(delay != 0);
	// while (diff >= delay) {
	if (diff >= delay) {
		sprite->Move(anim->GetDx(), anim->GetDy());
//		CollisionChecker::Singleton()->Check();
		lastTime += delay;
		if (!anim->GetContinuous()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
		}
	}
}

bool MovingAnimator::ShouldProgress(timestamp_t currTime) {
	return timestamp_diff(currTime, lastTime) >= anim->GetDelay();
}

MovingAnimator::MovingAnimator(bool _register) : Animator(_register),
 sprite(static_cast<Sprite*>(0)), anim(static_cast<MovingAnimation*>(0))
{ }

MovingAnimator::~MovingAnimator(void) { }

void MovingAnimator::Start (Sprite* s, MovingAnimation* a, timestamp_t t) {
	sprite	= s;
	anim 	= a;
	lastTime = t;
	state 	= ANIMATOR_RUNNING;
}


bool MovingAnimator::EnsureProgressable(unsigned int steps,
 timestamp_t currTime)
{
	timestamp_t backstep = steps * anim->GetDelay();
	bool result = true;
	// if backstepping is too large, return false
	if (backstep > currTime) result = false;
	else
		if (timestamp_diff(currTime, lastTime) < backstep)
			lastTime = currTime - backstep;
			
	return result;
} // MakeProgressable

Sprite *MovingAnimator::GetSprite(void) const { return sprite; }
MovingAnimation *MovingAnimator::getAnimation(void) const { return anim; }
//void MovingAnimator::__backoff::operator () (MovingAnimator* animator) const
//{
//	if (_backed) {
//		animator->sprite = s;
//		animator->anim = a;
//		animator->state = state;
//		std::cerr<<"Restored backoff s="<<s->getID()<<", a="<<
//		 a->GetId()<<", state="<<state<<std::endl;
//		_backed = false;
//		animator->lastTime = lastTime;
//		//animator->TimeShift(currTime - backupTime);
//	}
//}
//
//void MovingAnimator::__backoff::operator = (MovingAnimator* animator) {
//	timestamp_t currTime = getTimestamp();
//	// only save state if everything is non NULL
//	// (which means that it's not the first time the animtor is being
//	// started).
//	if (animator->sprite && animator->anim) {
//		s = animator->sprite;
//		a = animator->anim;
//		state = animator->state;
//		lastTime = animator->lastTime;
//		std::cerr<<"Saved backoff state: s="<<s->getID()<<
//		 ", a="<<a->GetId()<<", state="<<state<<std::endl;
//		_backed = true;
//		backupTime = currTime;
//	}
//}
//
//void MovingAnimator::BackOff(void) {
//	if (backoff)
//		if (
//		 ((anim->GetId() == 1002 || anim->GetId() == 1004)
//		  &&(backoff->a->GetId()==1002||backoff->a->GetId()==1004))
//		 ||
//		 ((anim->GetId()==1003||anim->GetId()==1005)
//		  &&(backoff->a->GetId()==1003||backoff->a->GetId()==1005))
//		)
//			;
//		else
//			(*backoff)(this);
//}
//
//void MovingAnimator::ForthOn(void) {
//	(*backoff) = this;
//}
//
//MovingAnimator::__backoff::__backoff(void) :
// s(static_cast<Sprite*>(0)),
// a(static_cast<MovingAnimation*>(0)),
// state(ANIMATOR_FINISHED),
// _backed(false)
//{ }
//
//bool MovingAnimator::__backoff::backed(void) const { return _backed; }



//			// diff0 = currTime - lastTime0
//			// diff1 = currTime - lastTime1
//			// lastTime1 = lastTime0 + delay
//			// diff1 = diff0 + (diff1 - diff0) <=>
//			// diff1 = + currTime - lastTime0
//			//         + currTime - lastTime1
//			//         - currTime + lastTime0  <=>
//			// diff1 = + currTime - lastTime0
//			//         + currTime - lastTime0
//			//         -delay
//			//         - currTime + lastTime0  <=>
//			// diff1 = + currTime - lastTime0
//			//         - delay                 <=>
//			// diff1 = diff0 - delay


//	if (currTime - lastTime >= anim->GetDelay()) {
//		sprite->Move(anim->GetDx(), anim->GetDy());
//		if (!anim->GetContinuous()) {
//			state = ANIMATOR_FINISHED;
//			NotifyStopped();
//		}
//		else {
//			lastTime += anim->GetDelay();
//			Progress(currTime);
//		}
//	}
