#include "GameStats.hpp"

GameStats::GameStats(SurfaceLoader *sl) {
	score = 0; lives = 3; level = 1;
	font_logo = TTF_OpenFont("resources/fonts/Crackman.ttf", 50);
	font_text = TTF_OpenFont("resources/fonts/Lemonhd.ttf",25);
}

void GameStats::Draw(SDL_Surface *screen) {
	SDL_Color logoColor = { 61, 171, 139 };
	SDL_Color textColor = { 255, 255, 255 };
	
	SDL_Rect logo_pos = { 520, 40 };
	logo = TTF_RenderUTF8_Blended(font_logo, "Pac-Man", logoColor);
	SDL_BlitSurface(logo, NULL, screen, &logo_pos);

}
/*
void GameStats::LoopDraw(SDL_Surface *screen) {
	
}*/

void GameStats::SetScore(unsigned int _score) {
	score = _score;
}

void GameStats::SetLives(unsigned int _lives) {
	lives = _lives;
}

void GameStats::SetLevel(unsigned int _level) {
	level = _level;
}

unsigned int GameStats::GetScore(void) const {
	return score;
}

unsigned int GameStats::GetLives(void) const {
	return lives;
}

unsigned int GameStats::GetLevel(void) const {
	return level;
}

void GameStats::AddScore(unsigned int _score) {
	score += _score;
}

void GameStats::ResetScore(void) {
	score = 0;
}

void GameStats::AddLife(void) {
	++lives;
}

bool GameStats::LoseLife(void) {
	if(!lives--) return true;
	return false;
}
