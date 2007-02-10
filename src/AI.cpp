#include "AI.hpp"

std::map<GameSprite*, ActorMovement*> AI::moves;

void AI::Stalker(GameSprite* ghost, Targets* targets){
}
void AI::Chicken(GameSprite* ghost, Targets* targets){
}
void AI::Random(GameSprite* ghost, Targets* target){
}

void AI::SetMoves(std::map<GameSprite*, ActorMovement*> _moves){
	moves = _moves;
}
