#include "GameStats.hpp"


GameStats::GameStats(
	SurfaceLoader * const sl,
	Sprite * const pac,
	Sprite * const bon,
	Uint32 const bg,
	CollisionChecker * const _cc)
:
	// SDL_Colors
	  logoColor(0x00, 0x80, 0xff)
	, textColor(0xff, 0xff, 0xff)
	, numColor(0x00, 0xff, 0xff)

	// TTF_Fonts
	, font_logo(TTF_OpenFont("resources/fonts/Crackman.ttf", 50))
	, font_text(TTF_OpenFont("resources/fonts/ATOMICCLOCKRADIO.TTF",25))
	, num_text(TTF_OpenFont("resources/fonts/ATOMICCLOCKRADIO.TTF", 25))
	, font_game_over(TTF_OpenFont("resources/fonts/Alias.ttf", 76))

	// Rectangles
	, ptitle_level(520, 150, 0, 0) // Levelz
	, ptitle_score(520, 200, 0, 0) // score
	, ptitle_lives(520, 250, 0, 0) // lives
	, ptitle_bonus(0, 0, 0, 0) // TODO is this needed?
	, plogo(520, 40, 0, 0)
	, ptitle_fruits(520, 300, 0, 0) // fruits
	, ppacman(705, 245, 0, 0) // 
	, pgameover(120, 250, 0, 0)
	, plives(740, 250, 0, 0)
	, pbonus(730, 295, 0, 0)
	, tele(496, 232 + LAYOUT_Y_OFFSET, 32, 32)
	, plevel(728, 150, 0, 0)
	, pscore(670, 200, 0, 0)
	
	// Surfaces
	, logo(TTF_RenderUTF8_Blended(font_logo, "Pac-Man", logoColor))
	, title_score(TTF_RenderUTF8_Blended(font_text,"Score", textColor))
	, title_lives(TTF_RenderUTF8_Blended(font_text,"Lives", textColor))
	, title_fruits(TTF_RenderUTF8_Blended(font_text,"Bonus",textColor))
	, title_seperator(NULL) // TODO is this needed?
	, fruit(NULL) // TODO is this needed?
	, pacman ( SurfaceLoader::getInstance()->
	   loadSurface("./resources/animation_films/pacman.png"))
	, title_level(TTF_RenderUTF8_Blended(font_text,"Level", textColor))
	, num_level(NULL) // TODO is this needed?
	, num_score(NULL) // TODO is this needed?
	, num_lives(NULL) // TODO is this needed?
	, game_over(NULL)
	, choco ( SurfaceLoader::getInstance()->
	   loadSurface("./resources/animation_films/chocobonus.png"))
	
	// Sprites
	, _bonus(bon) // bonus sprite
	, _pacman(pac) // pacman sprite
	
	// unsigned ints
	, score(0)
	, lives(PACMAN_LIVES)
	, level(1)
	, dots(3)//135) //TODO get the real dots
	
	// bool
	, bonus(false)
	, dead_game(false)

	// Uint32
	, _bg(bg) // background colour

	// Collision Checker
	, cc(_cc)
{ }


void GameStats::Draw(SDL_Surface *screen) {

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

	if(dead_game){
		game_over = TTF_RenderUTF8_Blended(font_game_over,
		  "Game Over, N00B", textColor);
		SDL_BlitSurface(game_over, NULL, screen, &pgameover);
	}
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
	std::cerr<<"dots left "<<--dots<<std::endl;
	return (dots < 0);
}

void GameStats::DrunkChocodrink(void){
	bonus = true;
	score += level*200 +300;
}

void GameStats::ShowBonus(void){
	if(dots == 70){
		_bonus->SetVisibility(true);
		cc->Register(_bonus, _pacman);
	}
}

void GameStats::ShowGameOver(void){
	dead_game=true;
	lives++;
}

GameStats::_SDL_Color::_SDL_Color(int _r, int _g, int _b) {
	r = _r, g = _g, b = _b; }
GameStats::_SDL_Rect::_SDL_Rect(int _x, int _y, int _w, int _h) {
	x = _x, y = _y, w = _w, h = _h; }
