#ifndef _AI_HPP_
#define _AI_HPP_

#include "ActorMovement.hpp"
#include "Ghost.hpp"
#include "Waypoint.hpp"
#include <map>

struct Targets {
	Sprite 
	 *pacman,
	 *lair;
	// Maybe more will be added
};

class AI {
	public :
	static void Think(Waypoint* waypoint, Ghost* ghost);
	static void SetMoves(std::map<GameSprite*, ActorMovement*> _moves);
	static void SetTargets(Targets* _targets);

	private :
	static std::map<GameSprite*, ActorMovement*> moves;
	static Targets* targets;
	static std::vector<spriteid_t> ids;
	static int distanceFromPacman(Waypoint *waypoint );
	//enum sprite_type {
		//KIRA,
		//NEAR,
	//	/MISA,
		//RYUK
	//};

	static void Stalker(Waypoint* waypoint, Ghost* ghost, Sprite* target);
	static void Chicken(Waypoint* waypoint, Ghost* ghost, Sprite* target);
	static void Random(Waypoint* waypoint, Ghost* ghost);
}; // AI

#endif
