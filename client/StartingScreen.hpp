#ifndef _STARTING_SCREEN_HPP_
#define _STARTING_SCREEN_HPP_

#include "commons.hpp"
#include "SurfaceLoader.hpp"
#include "client.hpp"

typedef GameData::io_bools _bools;
extern void ShowStartingScreen(SDL_Surface *splash, SDL_Surface *screen,
 _bools &bools, std::map<GameSprite*, ActorMovement*> &, timestamp_t currT);

#endif
