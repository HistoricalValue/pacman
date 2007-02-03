#ifndef _MOVINGANIMATOR_HPP_
#define _MOVINGANIMATOR_HPP_

#include "Animator.hpp"
#include "Sprite.hpp"
#include "MovingAnimation.hpp"

class MovingAnimator : public Animator {
	Sprite*			sprite;
	MovingAnimation*	anim;
	public:
	void Progress (timestamp_t currTime);
	void Start (Sprite* s, MovingAnimation* a, timestamp_t t);
	bool ShouldProgress (timestamp_t currTime);
	// Ensures that the animator will progress that many steps.
	// Return true if this is possible, false otherwise.
	bool EnsureProgressable(unsigned int steps, timestamp_t currTime);
	Sprite* GetSprite(void);
	MovingAnimator (bool _register = true);
	~MovingAnimator(void);
};

#endif
