#ifndef _FRAMERANGEANIMATOR_HPP_
#define _FRAMERANGEANIMATOR_HPP_

#include "Animator.hpp"
#include "Sprite.hpp"
#include "FrameRangeAnimation.hpp"

class FrameRangeAnimator : public Animator {
	Sprite*			sprite;
	FrameRangeAnimation*	anim;
	frame_t			currFrame;

	public:
	void Progress (timestamp_t currTime);
	void Start (Sprite* s, FrameRangeAnimation* a, timestamp_t t);
	bool ShouldProgress(timestamp_t currTime);
	// Ensures that the animator will progress that many steps.
	// Return true if this is possible, false otherwise.
	bool EnsureProgressable(unsigned int steps, timestamp_t currTime);
	Sprite* GetSprite(void);
	FrameRangeAnimation *GetAnimation(void);
	FrameRangeAnimator(bool _register = true);
	~FrameRangeAnimator(void);
};

#endif
