#include "AnimationFilmHolder.hpp"
#include <iostream>
#include "SDL/SDL.h"
#include "SurfaceLoader.hpp"
#include "Sprite.hpp"
#include "CollisionChecker.hpp"
#include "GameSprite.hpp"
#include "ObstacleSprite.hpp"
#include "ObstaclePlatform.hpp"
#include <stdlib.h>

#define W 800
#define H 600

Uint32 whitecolor, blackcolor;
SDL_Surface *screen = NULL;
int dx, dy = 0;
/*
void MoveSprite(Sprite *s) {
	SDL_Rect tmp = s->frameBox;
	int newx = tmp.x + dx; 
	int newy = tmp.y + dy;
	if( ( newx < 0 ) || ( newx + 32 > W ) )
		newx = 0;
	else newx = dx;
	if( ( newy < 0 ) || ( newy + 32 > H ) )
		newy = 0;
	else newy = dy;
	s->Move(newx, newy);
}
*/

void print(GameSprite *gs, void* c){
	std::cout <<"AAAAAA!!!\n";
}

int main_zar(int argc, char *argv[]) {	
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);

	screen = SDL_SetVideoMode( W, H, 32, SDL_SWSURFACE);
	whitecolor = SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF );
	blackcolor = SDL_MapRGB( screen->format, 0, 0, 0 );

	// isi  inserted code
	AnimationFilmHolder* afh = new AnimationFilmHolder(new std::string(
	 "./resources/config/animationfilms.config"));
	AnimationFilm* tehflim = afh->GetFilm("__test_bg");

	GameSprite *s1 = new GameSprite(0,0,tehflim,101);
	s1->SetWH(32, 32);

	ObstacleSprite *os1 = new ObstacleSprite(0,0,tehflim,102);
	os1->SetWH(200,32);
	ObstacleSprite *os2 = new ObstacleSprite(0,0,tehflim,103);
	os2->SetWH(32, 100);

	ObstaclePlatform *op = new ObstaclePlatform(100, 100);
	op->Add(os1,0,0);
	op->Add(os2,84, 32);
	op->SetCollisionCheck(s1, true);

	ObstacleSprite *wall = new ObstacleSprite(600, 100, tehflim,104);
	wall->SetWH(40,200);

	CollisionChecker::Singleton()->Register(wall, s1);

	s1->SetOnSmashed(&print);
	
	int platformcounter = 300;
	int right = 1;
	while(quit == false) {
		int start = SDL_GetTicks();
        	while(SDL_PollEvent(&event)) {
			if(event.type == SDL_KEYDOWN) {
				switch(event.key.keysym.sym) {
					case SDLK_UP: dy -= 4; break;
					case SDLK_DOWN: dy += 4; break;
					case SDLK_LEFT: dx -= 4; break;
					case SDLK_RIGHT: dx += 4; break;
					case SDLK_ESCAPE: quit = true; break;
					default: break;
				}
			}
			
			if(event.type == SDL_KEYUP) {
				switch(event.key.keysym.sym) {
					case SDLK_UP: dy += 4; break;
					case SDLK_DOWN: dy -= 4; break;
					case SDLK_LEFT: dx += 4; break;
					case SDLK_RIGHT: dx -= 4; break;
					default: break;
				}
			}

            		if(event.type == SDL_QUIT) {
                		quit = true;
            		}
		}
		SDL_FillRect(screen, NULL, blackcolor);
		if(!platformcounter) {
			right = -right;
			platformcounter = 300;
		}
		platformcounter--;
		op->Move(right,0); //always before any other move
		s1->Move(dx,dy);	
		CollisionChecker::Singleton()->Check();
		op->Display(screen);
		wall->Display(screen);
		s1->Display(screen);
		SDL_Flip(screen);
		while( SDL_GetTicks() - start < 1000 / 75 );
    	}
	SDL_Quit();
	return 0;
}
