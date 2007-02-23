#include "CollisionChecker.hpp"
#include "FrameRangeAnimator.hpp"
#include "AnimatorHolder.hpp"

void FrameRangeAnimator::Progress (timestamp_t currTime) {
	timestamp_t diff = timestamp_diff(currTime, lastTime);
	delay_t delay = anim->GetDelay();

//	while (diff >= delay) {
	if (diff >= delay) {
		if (currFrame == anim->GetEndFrame())
			currFrame = anim->GetStartFrame();
		else
			++currFrame;

//		sprite->Move(anim->GetDx(), anim->GetDy());
//		CollisionChecker::Singleton()->Check();
		sprite->SetFrame(currFrame);
		lastTime += delay;
//		diff = timestamp_diff(currTime, lastTime);

		if (currFrame == anim->GetEndFrame() && !anim->GetContinuous())
		{
			state = ANIMATOR_FINISHED;
			NotifyStopped();
			return;
		}
	}
}

FrameRangeAnimator::FrameRangeAnimator(bool _register) :
 Animator(_register), sprite(static_cast<Sprite*>(0)),
 anim(static_cast<FrameRangeAnimation*>(0)), currFrame(0xFF)
{ }

FrameRangeAnimator::~FrameRangeAnimator(void)
{ }

void FrameRangeAnimator::Start (Sprite* s, FrameRangeAnimation* a, timestamp_t t) {
	sprite = s;
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
	sprite->SetFrame(currFrame = anim->GetStartFrame());
}

bool FrameRangeAnimator::ShouldProgress(timestamp_t currTime) {
	return timestamp_diff(currTime, lastTime) >= anim->GetDelay();
}

bool FrameRangeAnimator::EnsureProgressable(unsigned int steps,
 timestamp_t currTime)
{
	timestamp_t backstep = steps * anim->GetDelay();
	bool result = true;
	// if backstepping is too large, return false
	if (backstep > currTime) result = false;
	else
		if (lastTime - currTime < backstep)
			lastTime = currTime - backstep;
			
	return result;
} // MakeProgressable

Sprite *FrameRangeAnimator::GetSprite(void) { return sprite; }
FrameRangeAnimation *FrameRangeAnimator::GetAnimation(void) { return anim; }
