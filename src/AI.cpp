#include "AI.hpp"

std::map<GameSprite*, ActorMovement*> AI::moves;
Targets* AI::targets;

void AI::Stalker(GameSprite* ghost, Sprite* target){
}
void AI::Chicken(GameSprite* ghost, Sprite* target){
}
void AI::Random(GameSprite* ghost, Sprite* target){
}

void AI::SetMoves(std::map<GameSprite*, ActorMovement*> _moves){
	moves = _moves;
}

void AI::SetTargets(Targets* _targets){
	targets = _targets;
}
