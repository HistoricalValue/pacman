#ifndef _GAMESTATS_HPP_
#define _GAMESTATS_HPP_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "SurfaceLoader.hpp"
#include "Sprite.hpp"
#include "CollisionChecker.hpp"
#include "config.h"

class GameStats {
	SDL_Surface 	*logo, *title_score, *title_lives, 
			*title_fruits, *title_seperator,
			*fruit, *pacman, *title_level, *num_level, 
	                *num_score, *num_lives, *choco;
        SDL_Rect ptitle_level, ptitle_score, ptitle_lives, 
	  ptitle_bonus, plogo, ptitle_fruits, ppacman, plives, pbonus;
        Sprite *_bonus, *_pacman;
	unsigned int 	score, lives, level, dots;
        bool bonus;
	TTF_Font *font_logo, *font_text, *num_text;
        Uint32 _bg;
	public:
	GameStats(SurfaceLoader*, Sprite*, Sprite*, Uint32);
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
        bool EatDot(void); // returns true if there are no dots left
        void DrunkChocodrink(void);
        void ShowBonus(void); //shows the bonus
};

#endif
