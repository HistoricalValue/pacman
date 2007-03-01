#ifndef _ANIMATIONFILM_HPP_
#define _ANIMATIONFILM_HPP_

#include "SDL/SDL.h"
#include <vector>
#include <string>
#include <assert.h>
#include <iostream>

class AnimationFilm {
    SDL_Surface		*bitmap;
    std::vector<SDL_Rect>	boxes;
    std::string			id;
    public:
    char		GetTotalFrames (void) const ;
    SDL_Surface	*GetBitmap (void) const ;
    const std::string 	&GetId (void) const ;
    const SDL_Rect	&GetFrameBox (unsigned char frameNo) const ;
    void 		DisplayFrame (SDL_Surface *d, SDL_Rect *at, char frameNo) const;
    AnimationFilm (SDL_Surface *_bitmap, const std::vector<SDL_Rect>& _boxes, const std::string &_id);
   friend std::ostream &operator<<(std::ostream&, AnimationFilm&);
};
#endif
