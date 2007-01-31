/* AnimationHolder
 *
 * Parses animation configuration file and creates animation objects.
 */

#ifndef __AnimationHolder_hpp__
#define __AnimationHolder_hpp__

#include <list>
#include <string>

#include "MovingAnimation.hpp"
#include "FrameRangeAnimation.hpp"

typedef std::list<MovingAnimation*> MovingAnimationList;
typedef std::list<FrameRangeAnimation*> FrameRangeAnimationList;
class AnimationHolder {
	MovingAnimationList mv_anims;
	FrameRangeAnimationList fr_anims;
	public :
	MovingAnimationList const& getMovingAnimations(void) const;
	FrameRangeAnimationList const& getFrameRangeAnimations(void) const;
	// get-ers return NULL if not found
	Animation* getAnimation(animid_t) const;
	MovingAnimation* getMovingAnimation(animid_t) const;
	FrameRangeAnimation* getFrameRangeAnimation(animid_t) const;
	// Con/de-struuctor
	AnimationHolder(std::string const& config_file_path);
	~AnimationHolder(void);
}; // AnimatioNParser

#endif // __AnimationHolder_hpp__
