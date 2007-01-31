#include "FrameRangeAnimation.hpp"

std::ostream& operator << (std::ostream& o, FrameRangeAnimation& a) {
	static char const space = ' ', tab = '\t';
	static char const startf[] 	= "Starting frame:";
	static char const endf[]	= "Ending frame:";
	return o << static_cast<MovingAnimation&>(a) << std::endl <<
	 tab << startf << space << static_cast<int>(a.start) << std::endl <<
	 tab << endf << space << static_cast<int>(a.end);
}

frame_t	FrameRangeAnimation::GetStartFrame (void) const { return start; }
void	FrameRangeAnimation::SetStartFrame (frame_t v) { start = v; }
frame_t	FrameRangeAnimation::GetEndFrame (void) const { return end; }
void	FrameRangeAnimation::SetEndFrame (frame_t v) { end = v; }

Animation* FrameRangeAnimation::Clone (animid_t newId) const {
	return new FrameRangeAnimation(
	 start, end, GetDx(), GetDy(), GetDelay(), GetContinuous(),
	 newId
	);
}

// Constructor
FrameRangeAnimation::FrameRangeAnimation (
	 frame_t s, frame_t e, 
	 offset_t dx, offset_t dy, delay_t d, bool c, animid_t id
	) : MovingAnimation(dx, dy, d, c, id), start(s), end(e) {}


