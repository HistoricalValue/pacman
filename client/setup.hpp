/* Setup private header file.
 *
 * No for public including.
 */

// Needed headers
#include <iterator>
#include "AI.hpp"

// Setup functions ---------------------------------------------------------
static void libs_setup(struct InitData const&, struct GameData &);
static void screen_setup(struct InitData const&, struct GameData &);
static void fetch_special_sprites(struct InitData const&, struct GameData&);
static void aktor_movements_setup(struct InitData const&, struct GameData&);
static void ss_aliases_setup(struct InitData const&, struct GameData&);
static void ai_setup(struct InitData const&, struct GameData&);
static void collision_setup(InitData const&, struct GameData&);

// Foreach - functors ------------------------------------------------------
//
// for_each_functor :: base struct for all for_each_functors. Provides
// the common member fields.
template <class arg_t> struct for_each_functor :
 public std::unary_function<arg_t, void>
{
	virtual void operator() (arg_t) = 0;
	for_each_functor(InitData const&, GameData&);
	virtual ~for_each_functor(void);
	protected : InitData const& d; GameData &r;
}; // struct for_each_functor
// SSAMS : Special Sprite Actor Movement Setup:
// Creates and setups an ActorMovement instance for each special sprite.
// The instances are saved in the result (GameData).
struct SSAMS : public for_each_functor<GameSprite*> {
	void operator() (GameSprite*);
	SSAMS(struct InitData const&, struct GameData&);
	private :
	std::vector<AnimationIDs>::const_iterator anids;
}; // struct SSAMS
// Fetches moving animations into the given list.
struct MovingAnimationFetcher :  public for_each_functor<const animid_t&> {
	void operator() (animid_t const&);
	MovingAnimationFetcher(InitData const&, GameData&,
	 std::list<MovingAnimation*>&);
	private :
	std::list<MovingAnimation*>& mv;
}; // struct MovingAnimationFetcher
// Fetches frame range animations into the given list.
struct FrameRangeAnimationFetcher :public for_each_functor<const animid_t&>{
	void operator() (animid_t const&);
	FrameRangeAnimationFetcher(InitData const&, GameData&,
	 std::list<FrameRangeAnimation*>&);
	private :
	std::list<FrameRangeAnimation*>& fr;
}; // struct FrameRangeAnimationFetcher
// Create and starts an appropriate animator with the given animation.
struct AnimatorSetup : public for_each_functor<Animation*> {
	void operator() (Animation*);
	AnimatorSetup(InitData const&, GameData&, GameSprite*,
	 std::vector<MovingAnimator*>&, std::vector<FrameRangeAnimator*>&);
	private :
	GameSprite *g;
	std::vector<MovingAnimator*>& mvtors;
	std::vector<FrameRangeAnimator*>& frtors;
}; // AnimatorSetup
// Register special sprites for collision checking for obstacle platforms
struct SSS_CollisionRegisterer : public for_each_functor<
 std::pair<obstplatid_t const, ObstaclePlatform*>&>
{
	void operator() (std::pair<obstplatid_t const, ObstaclePlatform*>&);
	SSS_CollisionRegisterer(InitData const&, GameData&);
}; // struct SSS_CollisionRegisterer
struct SOPCR { // Sprite - Obstacle Platform Collision Registerer
	void operator() (GameSprite*);
	SOPCR(ObstaclePlatform*);
	private :
	ObstaclePlatform *o;
}; // struct SOPRC
// Register all ghosts for collision checking with waypoints
struct GWCR : public for_each_functor<GameSprite*> {
	void operator() (GameSprite *ghost);
	GWCR(InitData const&, GameData&);
	private :
	std::list<Waypoint*> waypoints;
}; // struct GWCR