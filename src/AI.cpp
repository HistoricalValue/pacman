#include "AI.hpp"

std::map<GameSprite*, ActorMovement*> AI::moves;
Targets* AI::targets;

void AI::Think(Sprite *waypoint, Ghost* ghost){
}

void AI::Stalker(Ghost* ghost, Sprite* target){
}
void AI::Chicken(Ghost* ghost, Sprite* target){
}
void AI::Random(Ghost* ghost, Sprite* target){
}

void AI::SetMoves(std::map<GameSprite*, ActorMovement*> _moves){
	moves = _moves;
}

void AI::SetTargets(Targets* _targets){
	targets = _targets;
}
