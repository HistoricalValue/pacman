#include "FrameRangeAnimation.hpp"

std::ostream& operator << (std::ostream& o, FrameRangeAnimation& a) {
	static char const space = ' ', tab = '\t';
	static char const startf[] 	= "Starting frame:";
	static char const endf[]	= "Ending frame:";
	return o << startf << space << static_cast<int>(a.start)
	 << std::endl <<
	 tab << endf << space << static_cast<int>(a.end);
}

frame_t	FrameRangeAnimation::GetStartFrame (void) const { return start; }
void	FrameRangeAnimation::SetStartFrame (frame_t v) { start = v; }
frame_t	FrameRangeAnimation::GetEndFrame (void) const { return end; }
void	FrameRangeAnimation::SetEndFrame (frame_t v) { end = v; }

Animation* FrameRangeAnimation::Clone (animid_t newId) const {
	return new FrameRangeAnimation(
	 start, end, GetDelay(), GetContinuous(),
	 newId
	);
}

// Constructor
FrameRangeAnimation::FrameRangeAnimation (
	 frame_t s, frame_t e, 
	 /* offset_t dx, offset_t dy, */
	 delay_t d, bool c, animid_t _id
	) : Animation(_id), start(s), end(e), delay(d), continuous(c) {}

delay_t FrameRangeAnimation::GetDelay(void) const { return delay; }
bool FrameRangeAnimation::GetContinuous(void) const { return continuous; }
