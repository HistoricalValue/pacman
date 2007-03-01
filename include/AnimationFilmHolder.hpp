#ifndef _ANIMATIONFILMHOLDER_HPP_
#define _ANIMATIONFILMHOLDER_HPP_

#include <map>
#include <string>
#include "AnimationFilm.hpp"


class AnimationFilmHolder {
	typedef std::map<std::string, AnimationFilm*> FilmMap;
	FilmMap		filmMap;
//  Not used...
//  AnimationFilm	*filmMem;
	public:
	AnimationFilm *GetFilm (std::string const &id) const;
	AnimationFilmHolder (std::string const *path);
	~AnimationFilmHolder(void);
};

#endif
