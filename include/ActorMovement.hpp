/* Actor Movement
 *
 * Handles the animators of an actor sprite according to various
 * events, such as whether a key has been pressed or a collision happened.
 */

#ifndef __ActorMovement_hpp__
#define __ActorMovement_hpp__

#include <vector>

#include "commons.hpp"
#include "MovingAnimator.hpp"
#include "FrameRangeAnimator.hpp"
#include "GameSprite.hpp"
#include "CollisionChecker.hpp"

using namespace cs454_2006;

class ActorMovement {
	public :
	enum move_t {UP, RIGHT, DOWN, LEFT, NOWHERE = -1};
	ActorMovement(GameSprite *actor,
	 std::vector<MovingAnimator*> const &anitors,
	 std::vector<FrameRangeAnimator*> const &yums,
	 amc_t &amc,
	 timestamp_t currTime);
	void pressed(move_t direction, timestamp_t currTime);
	void released(move_t direction, timestamp_t currTime);
	void progress(timestamp_t currTime);
	void collided(GameSprite *who);
	MovingAnimator *getMovingAnimator(void);
	FrameRangeAnimator *getFrameRangeAnimator(void);
	enum move_t getLastMove(void) const;
	void setDelay(delay_t);
	// Suspends/resumes the currently running animator
	void suspend(timestamp_t);
	void resume(timestamp_t);
	private :
	struct AnimatorPair;
	struct SuspendFunctor;
	struct DelaySetter;
	GameSprite *actor;
	std::vector<AnimatorPair*> animators;
	AnimatorPair *w2g, *running; // actor wants to go
	bool w2g_collided;
	amc_t &amc;
}; // class ActorMovement

#endif // __ActorMovement_hpp__
