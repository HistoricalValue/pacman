/* Various support functions and classes/structures,
 * such as callbacks, used during the game.
 */

#ifndef __callbacks_hpp__
#define __callbacks_hpp__

#include "client.hpp"
#include "commons.hpp"
#include "Dot.hpp"
#include "FrameRangeAnimator.hpp"
#include "FrameRangeAnimation.hpp"
#include "AI.hpp"
#include "Scheduler.hpp"
#include "SoundManager.hpp"

struct _cocaclo {
	std::map<GameSprite*, ActorMovement*> *akmovs;

	_cocaclo(void); ~_cocaclo(void);
}; // struct _cocaclo

struct Callbacks {
	amc_t &get_amc(void);
	Sprite::CollisionCallback get_coca(void);
	_cocaclo &get_cocaclo(void); // get collision callback closure

	Callbacks(
	 CollisionChecker*,
	 Sprite::CollisionCallback);
	~Callbacks(void);
	private :
	struct _amc : public cs454_2006::amc_t {
		int operator() (Animator*) const; 
		_amc(CollisionChecker *); ~_amc(void);
		private :
		CollisionChecker *cc;
	};
	CollisionChecker *cc;
	_amc amc;
	Sprite::CollisionCallback coca;
	_cocaclo cocaclo;
}; // struct Callbacks

extern void collision_callback(Sprite*, Sprite*, void *c = CAST(void*, 0));
extern void cleanup(void);

struct Matcher : public Anim2SpriteMatcher {
	Sprite *operator() (Animation*) const;
	Matcher(SpriteHolder*);
	~Matcher(void);
};

struct AnimatorProgressor : public std::unary_function<
 std::pair<GameSprite *const, ActorMovement*>&, void>
{
	result_type operator() (argument_type);
	AnimatorProgressor(timestamp_t);
	private :
	timestamp_t timesand;
}; // struct AnimatorProgressor

// Closure information for dot callbacks
struct DotInfo {
	const uint8_t number_of_repeats;
	uint8_t repeats_made;
	DotInfo(uint8_t number_of_repeats); ~DotInfo(void);
}; // struct Dotinfo

// Callback for dot sprites
void DotAnimatorCallback(Animator*, void*);

// Callback for dot sprites callback data
struct Dot::_coca {
	CollisionChecker *cc;
	Sprite *pacman;
	GameStats *stat;
}; // struct Dot::_coca

#endif // __callbacks_hpp__
