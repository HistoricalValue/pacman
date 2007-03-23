#include "StartingScreen.hpp"
#include "SDL/SDL_ttf.h"
#include "AnimatorHolder.hpp"

void ShowStartingScreen(SDL_Surface *surf, SDL_Surface *screen,
 _bools &bools, std::map<GameSprite*, ActorMovement*> &akmovs,
 timestamp_t currTime)
{
	// suspend animators
	AnimatorHolder::suspendAllRunning(currTime);
	std::map<GameSprite*, ActorMovement*>::iterator ite;
	for (ite = akmovs.begin(); ite != akmovs.end(); ite++)
		ite->second->suspend(currTime);
	std::cerr<<currTime<<std::endl;
	
	TTF_Font *ttf_msg(TTF_OpenFont("resources/fonts/Alias.ttf", 32));
	SDL_Rect pmessage;
	SDL_Surface *msg; 
	SDL_Color col;
	col.r = 0xff; col.g = 0xff; col.b = 0xff;
	SDL_Event event;
	pmessage.x = 16; pmessage.y = 550; pmessage.w = 100;pmessage.h = 30;
	msg = TTF_RenderUTF8_Blended(
		ttf_msg, "Press any key to Continue", col);

	uint8_t blinker = 0;
	while (!bools.start) {
		bool new_events = false;
		while(SDL_PollEvent(&event))
			new_events = true;
		if (new_events) {
			switch(event.type) {
				case SDL_KEYUP:
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE :
							bools.exit = true;
							bools.game_exit =
							 true;
							return;
						default :
							bools.start = true; 
					}
					break;
				case SDL_QUIT:
					bools.exit = true;
					bools.game_exit = true;
					break;
			}

		}
		// capping
		switch(blinker++) {
			case 50 :
				blinker = 1;
			case 0 :
			std::cerr<<getTimestamp()<< " " <<static_cast<unsigned long int>(blinker)<<" OM"<< std::endl;
				SDL_BlitSurface(msg, NULL, screen,
				 &pmessage);
				break;
			case 25 :
				SDL_FillRect(screen, &pmessage, 0);
				break;
			default :
				break;
		}
		SDL_Flip(screen);
		SDL_Delay(20);
	}

	// Resume all animators
	timestamp_t restime = getTimestamp();
	AnimatorHolder::resumeAllExRunning(restime);
	std::map<GameSprite*, ActorMovement*>::iterator rite;
	for (rite = akmovs.begin(); rite != akmovs.end(); rite++)
		rite->second->resume(restime);

	std::cerr<<restime<<std::endl;
}
