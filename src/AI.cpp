#include "AI.hpp"
#include "commons.hpp"
#include <assert.h>
#include <math.h>

using namespace cs454_2006;

std::map<GameSprite*, ActorMovement*> AI::moves;
Targets* AI::targets;
std::vector<spriteid_t> AI::ids(4);




double AI::distanceFromPacman(Waypoint *waypoint ){
	int _x = abs(waypoint->GetX() -targets->pacman->GetX());
	int _y = abs(waypoint->GetY() - targets->pacman->GetY());
	return sqrt(_x*_x + _y*_y);
}

void AI::Think(Waypoint *waypoint, Ghost* ghost){
	ghoststate_t state = ghost->GetState();
	switch(state){
		case NORMAL:
			if(ghost->getID()==3003)
				Stalker(waypoint, ghost, targets->pacman);	
 			else if(ghost->getID()==3004){ 
				std::cerr<<"distance="<<distanceFromPacman(waypoint)<<std::endl;
				if(distanceFromPacman(waypoint)>100)
					Stalker(waypoint, ghost, targets->pacman);	
				else			
					Chicken(waypoint, ghost, targets->pacman);	
			}
			else if(ghost->getID()==3005)
				Random(waypoint, ghost);	
			else if(ghost->getID()==3006){
				if(distanceFromPacman(waypoint)>120)
					Random(waypoint, ghost);	
				else			
					Stalker(waypoint, ghost, targets->pacman);	
			}
			else
				assert(0);
//			Stalker(waypoint, ghost, targets->pacman);
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
	bool up = false, down = false, left = false, right = false;
	
	int xdiff = target->GetX() - ghost->GetX();
	int ydiff = target->GetY() - ghost->GetY();

	if(xdiff > 0) right = true;
	else if(xdiff < 0) left = true;
	if(ydiff > 0) down = true;
	else if(ydiff < 0) up = true;

	ActorMovement::move_t directions[4];
	short int counter = 0;
	ActorMovement *am = moves[ghost];
	ActorMovement::move_t lastmove = am->getLastMove();
	if(waypoint == targets->lair) lastmove = ActorMovement::NOWHERE;

	if(waypoint->canGoUp() && lastmove != ActorMovement::DOWN && up)
		directions[counter++] = ActorMovement::UP;
	if(waypoint->canGoDown() && lastmove != ActorMovement::UP && down)
		directions[counter++] = ActorMovement::DOWN;
	if(waypoint->canGoLeft() && lastmove != ActorMovement::RIGHT && left)
		directions[counter++] = ActorMovement::LEFT;
	if(waypoint->canGoRight() && lastmove != ActorMovement::LEFT && right)
		directions[counter++] = ActorMovement::RIGHT;

	if(counter)
		am->pressed(directions[rand() % counter], getCurrentTime());
	else
	Random(waypoint, ghost);	
	
}

void AI::Chicken(Waypoint* waypoint, Ghost* ghost, Sprite* target){
	bool up = false, down = false, left = false, right = false;
	
	int xdiff = target->GetX() - ghost->GetX();
	int ydiff = target->GetY() - ghost->GetY();

	if(xdiff > 0) left = true;
	else if(xdiff < 0) right = true;
	if(ydiff > 0) up = true;
	else if(ydiff < 0) down = true;

	ActorMovement::move_t directions[4];
	short int counter = 0;
	ActorMovement *am = moves[ghost];
	ActorMovement::move_t lastmove = am->getLastMove();

	if(waypoint->canGoUp() && lastmove != ActorMovement::DOWN && up)
		directions[counter++] = ActorMovement::UP;
	if(waypoint->canGoDown() && lastmove != ActorMovement::UP && down)
		directions[counter++] = ActorMovement::DOWN;
	if(waypoint->canGoLeft() && lastmove != ActorMovement::RIGHT && left)
		directions[counter++] = ActorMovement::LEFT;
	if(waypoint->canGoRight() && lastmove != ActorMovement::LEFT && right)
		directions[counter++] = ActorMovement::RIGHT;

	if(counter)
		am->pressed(directions[rand() % counter], getCurrentTime());
	else
	Random(waypoint, ghost);	
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

	//nf(!counter, "Waypoint must be disabled.\n");
	if(!counter) return;//DEBUG LINE
	am->pressed(directions[rand() % counter], getCurrentTime());
}

void AI::SetMoves(std::map<GameSprite*, ActorMovement*> _moves){
	moves = _moves;
	//std::map<GameSprite*, ActorMovement*>::const_iterator ite = _moves.begin();
	//ids[KIRA] = ite->first->getID();
	//ids[NEAR] = (*++ite).first->getID();
	//ids[MISA] = (*++ite).first->getID();
	//ids[RYUK] = (*++ite).first->getID();
}

void AI::SetTargets(Targets* _targets){
	targets = _targets;
}
