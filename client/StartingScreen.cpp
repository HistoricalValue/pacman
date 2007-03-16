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
	
        bool daflag = true;
	TTF_Font *ttf_msg(TTF_OpenFont("resources/fonts/Alias.ttf", 32));
	SDL_Rect pmessage;
	SDL_Surface *msg; 
	SDL_Color col;
	col.r = 0xff; col.g = 0xff; col.b = 0xff;
	SDL_Event event;
	pmessage.x = 16; pmessage.y = 550; pmessage.w = 100; pmessage.h = 30;
	msg = TTF_RenderUTF8_Blended(
		ttf_msg, "Press any key to Continue", col);
	while (!bools.start) {
		if(!SDL_PollEvent(&event))
			;
		else {
			switch(event.type) {
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

		}
		// capping
		SDL_Delay(500);
		if(daflag){
		  SDL_BlitSurface(msg, NULL, screen, &pmessage);
		  SDL_Flip(screen);
		  daflag = false;
		}
		else{
		  SDL_FillRect(screen, &pmessage, 0);
		  SDL_Flip(screen);
		  daflag = true;  
		}
	}

	// Resume all animators
	timestamp_t restime = getTimestamp();
	AnimatorHolder::resumeAllExRunning(restime);
	std::map<GameSprite*, ActorMovement*>::iterator rite;
	for (rite = akmovs.begin(); rite != akmovs.end(); rite++)
		rite->second->resume(restime);

	std::cerr<<restime<<std::endl;
}
