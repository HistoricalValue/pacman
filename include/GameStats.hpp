#ifndef _GAMESTATS_HPP_
#define _GAMESTATS_HPP_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "SurfaceLoader.hpp"
#include "Sprite.hpp"
#include "CollisionChecker.hpp"
#include "config.h"

class GameStats {
	struct _SDL_Color :
	 public SDL_Color { _SDL_Color(int r, int g, int b); };
	struct _SDL_Rect :
	 public SDL_Rect {_SDL_Rect(int x, int y, int w, int h); };
	const _SDL_Color 	logoColor, textColor, numColor;
	TTF_Font		*font_logo, *font_text, *num_text,
				*font_game_over;
	_SDL_Rect 		ptitle_level, ptitle_score, ptitle_lives, 
				ptitle_bonus, plogo, ptitle_fruits,
				ppacman, plives, pbonus, tele, plevel,
				pscore, pgameover;
	SDL_Surface 		* const logo, * const title_score,
				* const title_lives, 
				* const title_fruits,
				* const title_seperator,
				* const fruit, * const pacman,
				* const title_level, * num_level, 
				*num_score, * num_lives, * game_over,
				* const choco;
	Sprite			* const _bonus, * const _pacman;
	unsigned int 		score, lives, level;
	int16_t			dots;
	bool 			bonus, dead_game;
	Uint32 const		_bg;
	CollisionChecker	* const cc;
	public:
	GameStats(SurfaceLoader* const, Sprite* const, Sprite* const,
	 Uint32 const, CollisionChecker* const);
	void Draw(SDL_Surface*);
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
	void ShowGameOver(void);
};

#endif
