#include "commons.hpp"
#include "AnimationSetup.hpp"
#include "MovingAnimator.hpp"
#include "FrameRangeAnimator.hpp"
#include "AnimatorHolder.hpp"

using namespace cs454_2006;

AnimationData* setup_animations(SetupData* d) {
	AnimationData* result = new AnimationData;
	result->filmhold = new AnimationFilmHolder(d->animation_films);
	result->animhold = new AnimationHolder(*d->animations);
	result->spritehold = new SpriteHolder(
	 *d->sprites, result->filmhold);
	return result;
} // setup_animation

/********* Animation start up ************/
Anim2SpriteMatcher::Anim2SpriteMatcher(SpriteHolder* _sh) : sh(_sh) { }
Anim2SpriteMatcher::~Anim2SpriteMatcher(void) { }

enum AnimType {mv, fr};
struct AnimationStartFunctor : public std::unary_function<Animation*, void>
{
	void operator() (Animation* a);
	AnimationStartFunctor(enum AnimType _animt, timestamp_t ct,
	 Anim2SpriteMatcher const& _matcher);
	private :
	enum AnimType animt;
	timestamp_t currTime;
	Anim2SpriteMatcher const& matcher;
	void start_mv(Sprite* s, Animation* a);
	void start_fr(Sprite* s, Animation* a);
};

void start_animations(AnimationHolder* animhold, Anim2SpriteMatcher* matcher
 ,timestamp_t currTime)
{
	MovingAnimationList const& mv_anims=animhold->getMovingAnimations();
	FrameRangeAnimationList const& fr_anims = animhold->
	 getFrameRangeAnimations();

	std::for_each(mv_anims.begin(), mv_anims.end(),
	 AnimationStartFunctor(mv, currTime, *matcher));
	std::for_each(fr_anims.begin(), fr_anims.end(),
	 AnimationStartFunctor(fr, currTime, *matcher));
}

void AnimationStartFunctor::operator() (Animation* a) {
	Sprite* s = matcher(a);
	if (!s) return; // do not run anything for this animation
	switch (animt) {
		case mv :
			start_mv(s, a);
			break;
		case fr :
			start_fr(s, a);
			break;
		default :
			nf(-1, "Illegal switch state");
	}
}

AnimationStartFunctor::AnimationStartFunctor(enum AnimType _animt,
 timestamp_t ct, Anim2SpriteMatcher const& _matcher) :
 animt(_animt), currTime(ct), matcher(_matcher) { }


void AnimationStartFunctor::start_mv(Sprite* s, Animation* a) {
	MovingAnimation* mva =
	 dynamic_cast<MovingAnimation*>(a);
	nf(!mva, "Not a moving animation");
	MovingAnimator* mvator = new MovingAnimator;
	mvator->Start(s, mva, currTime);
	AnimatorHolder::MarkAsRunning(mvator);
}
void AnimationStartFunctor::start_fr(Sprite* s, Animation* a) {
	FrameRangeAnimation* fra =
	 dynamic_cast<FrameRangeAnimation*>(a);
	nf(!fra, "Not a frame range animation");
	FrameRangeAnimator* frator = new FrameRangeAnimator;
	frator->Start(s, fra, currTime);
	AnimatorHolder::MarkAsRunning(frator);
}
