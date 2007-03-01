#ifndef _GAMESTATS_HPP_
#define _GAMESTATS_HPP_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "SurfaceLoader.hpp"

class GameStats {
	SDL_Surface 	*logo, *title_score, *title_lives, 
			*title_fruits, *title_seperator,
			*fruit, *pacman, *title_level;
	unsigned int 	score, lives, level;
	TTF_Font *font_logo, *font_text;
	SDL_Color logoColor, textColor;
	
	public:
	GameStats(SurfaceLoader*);
	void Draw(SDL_Surface*);
  //void LoopDraw(SDL_Surface*);
	void SetScore(unsigned int);
	void SetLives(unsigned int);
	void SetLevel(unsigned int);
	unsigned int GetScore(void) const;
	unsigned int GetLives(void) const;
	unsigned int GetLevel(void) const;

	void AddScore(unsigned int);
	void ResetScore(void);
	void AddLife(void);
	bool LoseLife(void); //returns true if pacman dies
};

#endif
