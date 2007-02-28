#include "ObstaclePlatformAnimator.hpp"

#include "commons.hpp"

void ObstaclePlatformAnimator::Start(
 ObstaclePlatform *_platform,
 MovingAnimation *_animation,
 timestamp_t startingTime)
{
	platform = _platform;
	animation = _animation;
	lastTime = startingTime;
	state = ANIMATOR_RUNNING;
	std::cerr<<platform<<" "<<animation<<" "<<lastTime<<std::endl;
} // Start

void ObstaclePlatformAnimator::Progress(timestamp_t currTime) {
	delay_t delay = animation->GetDelay();
	timestamp_t diff = timestamp_diff(currTime, lastTime);
	if (diff >= delay) { // should progress
		// Move the thing
		platform->Move(animation->GetDx(), animation->GetDy());
		// Ignore continuity and stuff
		if (!animation->GetContinuous()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
		}
		// Update last time
		lastTime += delay;
	}
} // Progress

bool ObstaclePlatformAnimator::ShouldProgress(timestamp_t currTime) {
	std::cerr<<"asjpasjda"<<std::endl;
	return animation->GetDelay() >= timestamp_diff(lastTime, currTime);
} // ShouldProgress

ObstaclePlatform *ObstaclePlatformAnimator::getPlatform(void) const {
	return platform;
} // getPlatform

MovingAnimation *ObstaclePlatformAnimator::getAnimation(void) const {
	return animation;
} // getAnimation

ObstaclePlatformAnimator::ObstaclePlatformAnimator(bool _register) :
	Animator(_register),
	platform(CAST(ObstaclePlatform*, 0)),
	animation(CAST(MovingAnimation*, 0)),
	lastTime(CAST(timestamp_t, 0)) { }
ObstaclePlatformAnimator::~ObstaclePlatformAnimator(void) { }
