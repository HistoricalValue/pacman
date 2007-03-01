#include "AnimationFilmHolder.hpp"
#include "SurfaceLoader.hpp"
#include "commons.hpp"

#include <iostream>
#include <fstream>
#include <string.h>
#include <ctype.h>

using namespace cs454_2006;

struct tokener {
	tokener &operator++(void) { return advance(); };
	tokener &operator++(int) { return advance(); };
	char *operator*(void) { return t; };
	tokener(const char *_delim, char *l) : delim(_delim)
	{
		t = strtok(l, delim);
		if (!t) nf(-1, "Initial tokenising failed");
	};
	private :
	const char *delim;
	char *t;
	tokener &advance(void) {
		t = strtok(NULL, delim);
		if (!t) nf(-1, "No more tokens");
		return *this;
	};
}; // tokener
static AnimationFilm *loadFilm(char *config_line);
static SDL_Rect *torect(char *rect_config);
static bool isEmptyLine(const char *line);

AnimationFilmHolder::AnimationFilmHolder(std::string const *path) {
	std::ifstream fin(path->c_str(), std::ios::in);
	if (!fin)
		nf(-1, "Could not open file for reading");

	const int buf_size = 1 << 10;
	bool parse;
	// parse config file
	while (!fin.eof()) {
		char buf[buf_size];
		fin.getline(buf, buf_size);
		parse = (buf[0] != '#') && !isEmptyLine(buf);
		if (parse) {
			AnimationFilm *film;
			film = loadFilm(buf);
			if (film) {
				filmMap[film->GetId()] = film;
				std::cerr << "Loaded film " <<
				 *film;
//				 film->GetId() << std::endl;
			} else 
				nf(-1, "Could not load animation film.");
		}
	}
} // constructor

#define q(A) std::cout<<'"'<<(A)<<'"'<<std::endl
static AnimationFilm *loadFilm(char *l) {
	tokener tok(" ", l);

	struct data {
		const char *id, *path, *num;
		char **dims;
	} d;

	// read film ID
	d.id = *tok;

	// read film bitmap path
	d.path = *++tok;

	// read num of frames
	d.num = *++tok;

	// allocate memory for the frame boxes
	int fnum = strtol(d.num, NULL, 10);
	d.dims = static_cast<char**>(malloc(sizeof(char*) * fnum));
	if (!d.dims)
		nf(-1, "Could not allocate memory.");
	// read frame boxes
	for (int i = 0; i < fnum; i++)
		d.dims[i] = *++tok;

	// load image
	SurfaceLoader *sl = SurfaceLoader::getInstance();
	std::string path(d.path);
	SDL_Surface *surf = sl->loadSurface(path);
	
	// create vector with frame boxes
	std::vector<SDL_Rect> boxes;
	for (int i = 0; i < fnum; i++)
		boxes.push_back(*torect(d.dims[i]));

	// create ID
	std::string *filmid = new std::string(d.id);

	// create and return film
	return new AnimationFilm(surf, boxes, *filmid);
} // loadFilm()

// transform configuration file units to pixels
#define cun2px(A)	(A)
// Old one
// #define cun2px(A)	((A)<<3)
static SDL_Rect *torect(char *l) {
	tokener tok(",", l+1);
	SDL_Rect *result = new SDL_Rect;

	// get x
	result->x = cun2px(strtol(*tok, NULL, 10));
	// get y
	result->y = cun2px(strtol(*++tok, NULL, 10));
	// get w
	result->w = cun2px(strtol(*++tok, NULL, 10));
	// get h
	result->h = cun2px(strtol(*++tok, NULL, 10));

	// ready
	return result;
} // torect()

static bool isEmptyLine(const char *l) {
	bool result = true;
	int i = 0;

	while (l[i])
		if ( isspace(l[i]) == false) {
			result = false;
			break;
		}
	return result;
} // isEmptyLine()

AnimationFilm *AnimationFilmHolder::GetFilm(const std::string &id) const {
	FilmMap::const_iterator i = filmMap.find(id);
	assert(i != filmMap.end());
	return i->second;
} // GetFilm()

// Destructor
AnimationFilmHolder::~AnimationFilmHolder(void) {
	filmMap.clear();
} // destructor
