#include "StartingScreen.hpp"

typedef GameData::io_bools _bools;
void ShowStartingScreen(SDL_Surface *surf, SDL_Surface *screen,
 _bools &bools)
{
  SDL_Event event;
  blit(surf, screen,0,0);
  if(!SDL_PollEvent(&event))
    return;
  switch(event.type){
    case SDL_KEYUP:
      switch(event.key.keysym.sym){
        case SDLK_ESCAPE : bools.exit = true; return;
        default : bools.start = true; 
      }
    case SDL_QUIT:
      bools.exit = true;
      break;
  }
  
}
