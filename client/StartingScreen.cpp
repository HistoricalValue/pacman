#include "StartingScreen.hpp"

void ShowStartingScreen(SDL_Surface *surf, SDL_Surface *screen,
 _bools &bools)
{
	SDL_Event event;
	while (!bools.start) {
		if(!SDL_PollEvent(&event))
			;
		switch(event.type){
			case SDL_KEYUP:
				switch(event.key.keysym.sym) {
					case SDLK_ESCAPE :
						bools.exit = true;
						return;
					default :
						bools.start = true; 
				}
				break;
			case SDL_QUIT:
				bools.exit = true;
				break;
		}

		// capping
		SDL_Delay(17);
	}
}
