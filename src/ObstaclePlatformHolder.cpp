#include <iostream>
#include <vector>
#include <fstream>
#include "ObstaclePlatformHolder.hpp"
#include "commons.hpp"
using namespace cs454_2006;

static bool shouldParseLine(std::string const& line);
static void parseLine(SpriteHolder*,
 ObstaclePlatformHolder::obstplats_map& plats, std::string& line);

ObstaclePlatformHolder::ObstaclePlatformHolder(
 std::string const& cf, SpriteHolder* sh)
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
static std::ostream& operator<<(std::ostream&, plats_data&);

static void parseLine(SpriteHolder* sh,
 ObstaclePlatformHolder::obstplats_map& plats,
 std::string& line)
{
	std::list<std::string> delims;
	delims.push_back(" ");
	Tokeniser tok(line, delims);
	plats_data d;
	unsigned long int spritesnum;

	// Read platform ID
	d.id = cppstrtol(*tok, 10);
	// Read platform x and y
	d.x = cppstrtol(*++tok, 10);
	d.y = cppstrtol(*++tok, 10);
	// Read number of obstacle sprites and create table
	spritesnum = cppstrtol(*++tok, 10);
	//d.sprites = new plats_data::sprite_data[spritesnum];
	d.sprites.reserve(spritesnum);
	// Read sprites
	for (unsigned long int i = 0; i < spritesnum; i++) {
		// Read obstacle id
		d.sprites[i].s = dynamic_cast<ObstacleSprite*>
		 (sh->getSprite(cppstrtol(*++tok, 10)));
		nf(!d.sprites[i].s,
		 "Sprite specified in obstacle platforms "
		 "configuration file is not an obstacle sprite.");
		// Read sprite relative x and y
		d.sprites[i].x = cppstrtol(*++tok, 10);
		d.sprites[i].y = cppstrtol(*++tok, 10);
	}

	std::cerr<<"Parsed: "<<d<<std::endl;

	ObstaclePlatform* n00b = new ObstaclePlatform(d.x, d.y);
	for (unsigned long int i = 0; i < spritesnum; i++)
		n00b->Add(d.sprites[i].s,
		 d.sprites[i].x, d.sprites[i].y);

	// add to map
}

static bool shouldParseLine(std::string const& line) { 
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
	 PrintFunctor(std::ostream& o);
	 private:
	 std::ostream& o;
};

std::ostream& operator<<(std::ostream& o, plats_data& d) {
	static char const obstplat[] = "ObstaclePlatform: ";
	static char const xy[] = "(x,y) = ";
	static char const id[] = "id = ";
	static char const comma = ',';
	static char const rpar = ')';
	static char const sprites[] = "Obstacles: ";

	o<<obstplat<<std::endl<<xy<<d.x<<comma<<d.y<<rpar<<
	 std::endl<<id<<d.id<<std::endl<<sprites<<std::endl;
	
	std::for_each(d.sprites.begin(), d.sprites.end(),
	 PrintFunctor(o));
	return o<<std::endl;
}

void PrintFunctor::operator()(plats_data::sprite_data& s) {
	o << s.s;
}

PrintFunctor::PrintFunctor(std::ostream& _o) : o(_o) { }
