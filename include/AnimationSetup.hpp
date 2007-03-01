 /* AnimationSetup
 *
 * Setup functions and data structures for the animation part of the game
 * (Animation, Animator, Sprite and subclasses).
 */

#ifndef __AnimationSetup_hpp__
#define __AnimationSetup_hpp__
#include <string>
#include "AnimationFilmHolder.hpp"
#include "AnimationHolder.hpp"
#include "SpriteHolder.hpp"
#include "ObstaclePlatformHolder.hpp"
#include "WaypointHolder.hpp"
#include "commons.hpp"

/* ********************* Set up part ***********************/

// Contains the file paths to configuration files.
struct SetupData {
	std::string *animation_films; // for AnimationFilmHolder
	std::string *animations; // For AnimationHolder
	std::string *sprites; // For SpriteHolder
	std::string *obstacle_platform; // For ObstaclePlatformHolder
	std::string *waypoints; // For WaypointHolder
};

// Contains the holders after initialisation
struct AnimationData {
	AnimationFilmHolder *filmhold; // animation film holder
	AnimationHolder *animhold; // animation holder
	SpriteHolder *spritehold; // sprite holder
	ObstaclePlatformHolder *plathold; // obstacle platform 
	WaypointHolder *wayhold; // waypoint holder
};

AnimationData *setup_animations(SetupData*);


/* *********************** Animation start part *******************/
struct Anim2SpriteMatcher : public std::unary_function<Animation const*, 
 Sprite*>
{
	// Returns the Sprite which coresponds to the given animation.
	// NULL is returned if this animation should not be run.
	virtual Sprite *operator() (Animation *a) const = 0;
	Anim2SpriteMatcher(SpriteHolder*);
	virtual ~Anim2SpriteMatcher(void);
	protected :
	SpriteHolder *sh;
};

void start_animations(AnimationHolder*, Anim2SpriteMatcher*,
 timestamp_t currTime, void (*DotAnimatorCallback)(Animator*, void*));

#endif // __AnimationSetup_hpp__
