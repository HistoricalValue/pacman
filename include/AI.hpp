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
	static void SetMoves(std::map<GameSprite*, ActorMovement*> _moves);
	static void SetTargets(Targets* _targets);

	private :
	static std::map<GameSprite*, ActorMovement*> moves;
	static Targets* targets;

	static void Stalker(GameSprite* ghost, Sprite* target);
	static void Chicken(GameSprite* ghost, Sprite* target);
	static void Random(GameSprite* ghost, Sprite* target);
}; // AI

#endif
