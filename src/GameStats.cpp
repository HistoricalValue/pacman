#include "GameStats.hpp"


GameStats::GameStats(SurfaceLoader *sl, Sprite *pac, Sprite *bon, Uint32 bg) {
        score = 0; lives = 3; level = 1; dots = 139, bonus = false;
        _bonus = bon; _pacman = pac; _bg = bg;
	font_logo = TTF_OpenFont("resources/fonts/Crackman.ttf", 50);
	font_text = TTF_OpenFont("resources/fonts/ATOMICCLOCKRADIO.TTF",25);
	num_text = TTF_OpenFont("resources/fonts/ATOMICCLOCKRADIO.TTF", 25);
	// colors init
	SDL_Color logoColor = { 0, 128, 255};
	SDL_Color textColor = { 255, 255, 255 };
	// rendering surfaces
	// the 'pacman' logo
	plogo.x = 520; plogo.y = 40;
	logo = TTF_RenderUTF8_Blended(font_logo, "Pac-Man", logoColor);
	// lvlz
	ptitle_level.x = 520; ptitle_level.y = 150;
	title_level = TTF_RenderUTF8_Blended(font_text, "Level", textColor);
	// score
	ptitle_score.x = 520; ptitle_score.y = 200;
	title_score = TTF_RenderUTF8_Blended(font_text, "Score", textColor);
	// lives
	ptitle_lives.x = 520; ptitle_lives.y = 250;
	title_lives = TTF_RenderUTF8_Blended(font_text, "Lives", textColor);
	// fruits
	ptitle_fruits.x = 520; ptitle_fruits.y = 300;
	title_fruits= TTF_RenderUTF8_Blended(font_text, "Bonus", textColor);
	
	ppacman.x = 705; ppacman.y = 245;
	pacman=SurfaceLoader::getInstance()->loadSurface("./resources/animation_films/pacman.png");
	pbonus.x = 730; pbonus.y = 295;
        choco=SurfaceLoader::getInstance()->loadSurface("./resources/animation_films/chocobonus.png");
}


void GameStats::Draw(SDL_Surface *screen) {

	SDL_Color numColor = {0, 255, 255 };	
	SDL_Rect tele = {496,232+LAYOUT_Y_OFFSET,32,32};
	SDL_Rect plevel = {728, 150}, pscore = {670, 200}, plives = {740, 250};
	SDL_FillRect(screen, &tele, _bg);
	SDL_BlitSurface(logo, NULL, screen, &plogo);
	SDL_BlitSurface(title_level, NULL, screen, &ptitle_level);
	SDL_BlitSurface(title_score, NULL, screen, &ptitle_score);
	SDL_BlitSurface(title_lives, NULL, screen, &ptitle_lives);
	SDL_BlitSurface(title_fruits, NULL, screen, &ptitle_fruits);
	SDL_BlitSurface(pacman, NULL, screen, &ppacman);
	char buff[8];


	sprintf(buff, "%03d", level);
	num_level = TTF_RenderUTF8_Blended(num_text, buff, numColor);
	SDL_BlitSurface(num_level, NULL, screen, &plevel);

	sprintf(buff, "%06d", score);
	num_score = TTF_RenderUTF8_Blended(num_text,buff, numColor);
	SDL_BlitSurface(num_score, NULL, screen, &pscore);
	
	sprintf(buff, "x%d", lives);
	num_lives = TTF_RenderUTF8_Blended(num_text,buff, numColor);
	SDL_BlitSurface(num_lives, NULL, screen, &plives);

	if(bonus)
	       SDL_BlitSurface(choco, NULL, screen, &pbonus);
}

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
	return (!lives--);
}

bool GameStats::EatDot(void){
        ShowBonus();
        return (!--dots);
}

void GameStats::DrunkChocodrink(void){
        bonus = true;
	score += level*200 +300;
}

void GameStats::ShowBonus(void){
  if(dots == 70){
    _bonus->SetVisibility(true);
    CollisionChecker::Singleton()->Register(_bonus, _pacman);
  }
  
}
