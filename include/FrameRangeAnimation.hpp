#ifndef _FRAMERANGEANIMATION_HPP_
#define _FRAMERANGEANIMATION_HPP_

#include <ostream>

#include "MovingAnimation.hpp"

typedef unsigned char frame_t;

class FrameRangeAnimation : public Animation {
	frame_t start, end;
	delay_t delay;
	bool continuous;
public:
	frame_t	GetStartFrame (void) const;
	void	SetStartFrame (frame_t v);
	frame_t	GetEndFrame (void) const;
	void	SetEndFrame (frame_t v);
	delay_t GetDelay(void) const;
	void    SetDelay(delay_t delay);
	bool	GetContinuous(void) const;
	void	SetContinuous(bool v);
	Animation *Clone (animid_t newId) const;
	friend std::ostream &operator << (std::ostream&,
	 FrameRangeAnimation&);
	FrameRangeAnimation (
	 frame_t s, frame_t e, 
	 /* offset_t dx, offset_t dy, */
	 delay_t d, bool c, animid_t id
	);
};

#endif
