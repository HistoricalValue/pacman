#include "AI.hpp"
#include <assert.h>

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

	if(waypoint->canGoUp())
		directions[counter++] = ActorMovement::UP;
	if(waypoint->canGoDown())
		directions[counter++] = ActorMovement::DOWN;
	if(waypoint->canGoLeft())
		directions[counter++] = ActorMovement::LEFT;
	if(waypoint->canGoRight())
		directions[counter++] = ActorMovement::RIGHT;

	moves[ghost]->pressed(directions[rand() % counter], SDL_GetTicks());
}

void AI::SetMoves(std::map<GameSprite*, ActorMovement*> _moves){
	moves = _moves;
}

void AI::SetTargets(Targets* _targets){
	targets = _targets;
}
