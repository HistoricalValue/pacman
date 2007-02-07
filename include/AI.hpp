#ifndef _AI_HPP_
#define _AI_HPP_

#include "ActorMovement.hpp"
#include <map>

struct Targets {
	Sprite 
	 *pacman,
	 *lair;
	// Maybe more will be added
};

class AI {
	public :
	static void Think(GameSprite* ghost);
	private :
	static std::map<GameSprite*, ActorMovement*> moves;

	static void Hunter(GameSprite* ghost, Targets* targets);
	static void Chicken(GameSprite* ghost, Targets* targets);
	static void Random(GameSprite* ghost, Targets* target);
}; // AI

#endif
