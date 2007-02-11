#include "AI.hpp"
#include "commons.hpp"
#include <assert.h>

using namespace cs454_2006;

std::map<GameSprite*, ActorMovement*> AI::moves;
Targets* AI::targets;

void AI::Think(Waypoint *waypoint, Ghost* ghost){
	ghoststate_t state = ghost->GetState();
	switch(state){
		case NORMAL:
			Random(waypoint, ghost);
			break;
		case SCARED:
			Chicken(waypoint, ghost, targets->pacman);
			break;
		case RETREAT:
			Stalker(waypoint, ghost, targets->lair);
			break;
		default:
			assert(0);
	}
}

void AI::Stalker(Waypoint* waypoint, Ghost* ghost, Sprite* target){
/*	bool up = false, down = false, left = false, right = false;
	
	int xdiff = target->GetX() - ghost->GetY();
	int ydiff = target->GetY() - ghost->GetY();

	if(xdiff > 0) right = true;
	else if(xdiff < 0) left = true;
	if(ydiff > 0) down = true;
	else if(ydiff < 0) up = true;
*/	
}
void AI::Chicken(Waypoint* waypoint, Ghost* ghost, Sprite* target){
}
void AI::Random(Waypoint* waypoint, Ghost* ghost){
	ActorMovement::move_t directions[4];
	short int counter = 0;
	ActorMovement *am = moves[ghost];
	ActorMovement::move_t lastmove = am->getLastMove();

	if(waypoint->canGoUp() && lastmove != ActorMovement::DOWN)
		directions[counter++] = ActorMovement::UP;
	if(waypoint->canGoDown() && lastmove != ActorMovement::UP)
		directions[counter++] = ActorMovement::DOWN;
	if(waypoint->canGoLeft() && lastmove != ActorMovement::RIGHT)
		directions[counter++] = ActorMovement::LEFT;
	if(waypoint->canGoRight() && lastmove != ActorMovement::LEFT)
		directions[counter++] = ActorMovement::RIGHT;

	am->pressed(directions[rand() % counter], getCurrentTime());
}

void AI::SetMoves(std::map<GameSprite*, ActorMovement*> _moves){
	moves = _moves;
}

void AI::SetTargets(Targets* _targets){
	targets = _targets;
}
