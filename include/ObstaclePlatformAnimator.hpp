/* Obstacle Platform Animator
 *
 * Provides the animator functionality for the obstacle platforms.
 */

#ifndef __ObstaclePlatformAnimator_hpp__
#define __ObstaclePlatformAnimator_hpp__

#include "Animator.hpp"
#include "ObstaclePlatform.hpp"
#include "MovingAnimation.hpp"

class ObstaclePlatformAnimator : public Animator {
	public :
	void Start(ObstaclePlatform*, MovingAnimation*, timestamp_t start);
	void Progress(timestamp_t currTime);
	bool ShouldProgress(timestamp_t currTime) const;
	ObstaclePlatform *getPlatform(void) const;
	MovingAnimation *getAnimation(void) const;

	ObstaclePlatformAnimator(bool _register = true);
	~ObstaclePlatformAnimator(void);

	private :
	ObstaclePlatform *platform;
	MovingAnimation *animation;
	timestamp_t lastTime;
}; // class ObstaclePlatformAnimator
#endif // __ObstaclePlatformAnimator_hpp__
