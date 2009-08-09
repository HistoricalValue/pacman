#include <iostream>
#include <vector>
#include <fstream>
#include "ObstaclePlatformHolder.hpp"
#include "commons.hpp"
#include <algorithm>
using namespace cs454_2006;

static bool shouldParseLine(std::string const &line);
static void parseLine(SpriteHolder*,
 ObstaclePlatformHolder::obstplats_map &plats, std::string &line);

ObstaclePlatformHolder::ObstaclePlatformHolder(
 std::string const &cf, SpriteHolder *sh)
{
	std::string line;
	std::ifstream fin(cf.c_str(), std::ios::in);

	if (!fin)
		nf( -1, "Could not load Obstacle Platform config file");

	while (!fin.eof()) {
		getline(fin, line);
		if (shouldParseLine(line))
			parseLine(sh, plats, line);
	}
}

struct plats_data {
	struct sprite_data {
	ObstacleSprite *s;
	unsigned int x, y;
	};
	std::vector<sprite_data> sprites;
	unsigned int x, y;
	obstplatid_t id;
};
static std::ostream &operator<<(std::ostream&, plats_data&);

#define CONVERTX(A) (A)
#define CONVERTY(A) ((A) + 40)
static void parseLine(SpriteHolder *sh,
 ObstaclePlatformHolder::obstplats_map &plats,
 std::string &line)
{
	std::list<std::string> delims;
	delims.push_back(" ");
	Tokeniser tok(line, delims);
	plats_data d;
	unsigned long int spritesnum;

	// Read platform ID
	d.id = cppstrtol(*tok, 10);
	// Read platform x and y
	d.x = CONVERTX(cppstrtol(*++tok, 10));
	d.y = CONVERTY(cppstrtol(*++tok, 10));
	// Read number of obstacle sprites and create table
	spritesnum = cppstrtol(*++tok, 10);
	//d.sprites = new plats_data::sprite_data[spritesnum];
	d.sprites.reserve(spritesnum);
	// Read sprites
	for (unsigned long int i = 0; i < spritesnum; i++) {
		d.sprites.push_back(*new plats_data::sprite_data);
		// Read obstacle id
		d.sprites[i].s = dynamic_cast<ObstacleSprite*>
		 (sh->getSprite(cppstrtol(*++tok, 10)));
		nf(!d.sprites[i].s,
		 "Sprite specified in obstacle platforms "
		 "configuration file is not an obstacle sprite.");
		// Set sprite non-visible to avoid displaying by the
		// sprite holder.
		d.sprites[i].s->SetVisibility(false);
		// Read sprite relative x and y
		d.sprites[i].x = cppstrtol(*++tok, 10);
		d.sprites[i].y = cppstrtol(*++tok, 10);
	}

	std::cerr<<"===================="<<std::endl<<d<<std::endl<<
	 "========================="<<std::endl;

	ObstaclePlatform *n00b = new ObstaclePlatform(d.x, d.y);
	for (unsigned long int i = 0; i < spritesnum; i++)
		n00b->Add(d.sprites[i].s,
		 d.sprites[i].x, d.sprites[i].y);

	// add to the map
	plats[d.id] = n00b;
}
#undef CONVERTX
#undef CONVERTY

static bool shouldParseLine(std::string const &line) { 
	bool result = false;
	if (!Tokeniser::isEmptyLine(line)) {
		if (!Tokeniser::isCommentLine(line))
			result = true;
	}

	return result;
}

struct PrintFunctor : public std::unary_function<plats_data::sprite_data,
 void>{
	 void operator()(plats_data::sprite_data&);
	 PrintFunctor(std::ostream &o);
	 private:
	 std::ostream &o;
};

std::ostream &operator<<(std::ostream &o, plats_data &d) {
	static char const obstplat[] = "ObstaclePlatform: ";
	static char const xy[] = "(x,y) = ";
	static char const id[] = "id = ";
	static char const comma = ',';
	static char const pars[] = "()";
	static char const sprites[] = "Obstacles: ";

	o<<obstplat<<std::endl<<xy<<pars[0]<<d.x<<comma<<d.y<<pars[1]<<
	 std::endl<<id<<d.id<<std::endl<<sprites;
	
	std::for_each(d.sprites.begin(), d.sprites.end(), PrintFunctor(o));
	return o;
}

void PrintFunctor::operator()(plats_data::sprite_data &s) {
	o<<std::endl<<*s.s;
}

PrintFunctor::PrintFunctor(std::ostream &_o) : o(_o) { }

// Displaying platforms
struct DisplayFunctor : public std::unary_function<
 std::pair<short unsigned int const, ObstaclePlatform*>, void>
{
	void operator()(std::pair<short unsigned int const,
	 ObstaclePlatform*>&);
	DisplayFunctor(SDL_Surface*);
	private :
	SDL_Surface *destination;
};

void ObstaclePlatformHolder::displayPlatforms(SDL_Surface *d) {
	std::for_each(plats.begin(), plats.end(), DisplayFunctor(d));
} // displayPlatforms

DisplayFunctor::DisplayFunctor(SDL_Surface *_destination) :
 destination(_destination) { }

void DisplayFunctor::operator() (std::pair<short unsigned int const,
 ObstaclePlatform*>& p)
{
	p.second->Display(destination);
}

ObstaclePlatformHolder::obstplats_map&
ObstaclePlatformHolder::getObstaclePlatforms(void) {
	return plats;
}

ObstaclePlatform *ObstaclePlatformHolder::getObstaclePlatform(
 obstplatid_t id)
{
	return plats[id];
}
