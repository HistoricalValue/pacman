#include <fstream>
#include <algorithm>
#include "SpriteHolder.hpp"
#include "commons.hpp"
#include "GameSprite.hpp"
#include "ObstacleSprite.hpp"
#include "Ghost.hpp"
#include "Dot.hpp"

// implementation headers
#include "config.h"

using namespace cs454_2006;

struct sprite_data {
	int x, y, z;
	spriteid_t id;
	AnimationFilm *film;
};

static void parseConfigFile(std::string&, AnimationFilmHolder*,
 SpriteHolder::SpritesMap&);
static bool shouldParseLine(std::string&);
static bool isCommentLine(std::string&);
static void parseLine(Tokeniser**, AnimationFilmHolder*, std::string&,
 std::list<std::string>&, SpriteHolder::SpritesMap&);

namespace cs454_2006 {
struct ListInit : public std::unary_function<Sprite const*, void> {
	void operator() (Sprite*);
	ListInit(
	 std::list<Sprite*>& all,
	 std::list<GameSprite*>& game,
	 std::list<ObstacleSprite*>& obst);
	private :
	std::list<Sprite*>& all;
	std::list<GameSprite*>& game;
	std::list<ObstacleSprite*>& obst;
};
} // namespace cs454_2006

// Constructor
SpriteHolder::SpriteHolder(std::string &cfp, AnimationFilmHolder *afh) {
	parseConfigFile(cfp, afh, sprites);
	
	// set up lists
	SpritesMap::iterator ite;
	for (ite = sprites.begin(); ite != sprites.end(); ite++)
		std::for_each(
		 ite->second.begin(),
		 ite->second.end(),
		 ListInit(allsprites, gamesprites, obstaclesprites)
		);
} // Constructor

// Destructor
SpriteHolder::~SpriteHolder(void) {}

// Add/remove sprites
void SpriteHolder::addSprite(Sprite *s, int z) {
	sprites[z].push_back(s);
} // addSprite
Sprite *SpriteHolder::removeSprite(Sprite *s) {
	SpritesMap::iterator ite = sprites.begin();
	while (ite != sprites.end()) { // for each z priority
		std::list<Sprite*>::iterator lite = ite->second.begin();
		while (lite != ite->second.end()) { // for each sprite
			// search sprites to spot s
			if (*lite == s) { // found it
				// remove it
				ite->second.remove(s);
				std::cerr<<s<<" --- ";db(" removed sprite");
				// stop searching
				break;
			}
			lite++;
		}
		ite++;
	}
	return s;
} // removeSprite

// Mass manipulation
void SpriteHolder::displaySprites(SDL_Surface *dst) {
	SpritesMap::iterator ite = sprites.begin();
	while (ite != sprites.end()) {
		std::list<Sprite*>::iterator lite = ite->second.begin();
		while (lite != ite->second.end()) {
			if ((*lite)->IsVisible())
				(*lite)->Display(dst);
			lite++;
		}
		ite++;
	}
} // displaySprites

static void parseConfigFile(std::string &path, AnimationFilmHolder *afh,
 SpriteHolder::SpritesMap &sprites)
{
	// open input stream to configuration file
	std::ifstream fin(path.c_str());
	// line buffer
	std::string buf;

	// set up
	Tokeniser *tok;
	std::list<std::string> delims;
	delims.push_back(" ");

	while (!fin.eof()) {
		getline(fin, buf);
		if (shouldParseLine(buf))
			parseLine(&tok, afh, buf, delims, sprites);
	}
} // parseConfigFile

static bool shouldParseLine(std::string &line) {
	bool result = false;
	if (!Tokeniser::isEmptyLine(line))
		result = !isCommentLine(line);
	return result;
} // shouldParseLine

static bool isCommentLine(std::string &line) {
	return line.at(0) == '#';
} // isCommentLine

#define CONVERTX(A) ((A) + LAYOUT_X_OFFSET)
#define CONVERTY(A) ((A) + LAYOUT_Y_OFFSET)
static void parseLine(Tokeniser **tokptr, AnimationFilmHolder *afh,
 std::string &line, std::list<std::string>& delims,
 SpriteHolder::SpritesMap &sprites)
{
	Tokeniser *tok = new Tokeniser(line, delims);

	*tokptr = tok;
	sprite_data d;

	// read sprite id
	d.id = cppstrtol(**tok, 10);
	// read x
	d.x = CONVERTX(cppstrtol(*++*tok, 10));
	// read y
	d.y = CONVERTY(cppstrtol(*++*tok, 10));
	// z-order
	d.z = cppstrtol(*++*tok, 10);
	// read animation film id
	d.film = afh->GetFilm(*++*tok);

	// create and add sprite
	Sprite *s;
	if (d.id < 1000) { // ids 0 - 1000 are obstacles
		s = new ObstacleSprite(d.x, d.y, d.film, d.id);
	} else 
	if (d.id >= GHOST_SPRITE_ID_FIRST &&
	 d.id < GHOST_SPRITE_ID_LAST
	) { // ghost sprites
		s = new Ghost(d.x, d.y, d.film, d.id);
	} 
	else if (d.id >= DOT_SPRITE_ID_FIRST &&
	 d.id < DOT_SPRITE_ID_LAST
	) { // dot sprites
		// read also number of animation repeats
		uint8_t numrepeats = cppstrtol(*++*tok, 10);
		s = new Dot(d.x, d.y, d.film, d.id, numrepeats);
	} else { // rest ids are game sprites
		s = new GameSprite(d.x, d.y, d.film, d.id);
	}
	sprites[d.z].push_back(s);
	db("Created sprite");
	std::cerr << *s << std::endl;
} // parseLine
#undef CONVERTX
#undef CONVERTY

namespace cs454_2006 {
struct SpriteMatchPredicate : public std::unary_function<Sprite*, bool> {
	bool operator () (Sprite *s) { return s->getID() == id; }
	SpriteMatchPredicate(spriteid_t _id) : id(_id) { }
	private :
	spriteid_t id;
};
} // namespace cs454_2006

Sprite *SpriteHolder::getSprite(spriteid_t id) {
	std::list<Sprite*>::iterator spite;
	if ( (spite = std::find_if(
	 allsprites.begin(),
	 allsprites.end(),
	 cs454_2006::SpriteMatchPredicate(id))) == allsprites.end()
	) {
		std::cerr<<id<<std::endl;
		nf(-1, "Could not find sprite");
	}
	return *spite;
} // getSprite

std::list<Sprite*> const &SpriteHolder::getSprites(void) const
	{ return allsprites; }
std::list<GameSprite*> const &SpriteHolder::getGameSprites(void) const
	{ return gamesprites; }
std::list<ObstacleSprite*> const &SpriteHolder::getObstacleSprites(void) const
	{ return obstaclesprites; }

void ListInit::operator() (Sprite *s) {
	if (s->getID() < 1000) { // obstacle
		ObstacleSprite *os = dynamic_cast<ObstacleSprite*>(s);
		nf(!os, "Sprite with ID less than 1000 is not an "
		 "ObstacleSprite");
		obst.push_back(os);
	} else { // game
		GameSprite *gm = dynamic_cast<GameSprite*>(s);
		nf(!gm, "Sprite with ID more than 1000 is not a "
		 "GameSprite");
		game.push_back(gm);
	}
	all.push_back(s);
}

ListInit::ListInit(
 std::list<Sprite*>& _all,
 std::list<GameSprite*>& _game,
 std::list<ObstacleSprite*>& _obst
) : all(_all), game(_game), obst(_obst) { }
