#include <fstream>
#include "ObstaclePlatformHolder.hpp"
#include "commons.hpp"
using namespace cs454_2006;

static bool shouldParseLine(std::string const& line);
static void parseLine(ObstaclePlatformHolder::obstplats_map& plats,
 std::string& line);

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
			parseLine(plats, line);
	}
}

struct plats_data {
	struct sprite_data {
	ObstacleSprite *s;
	unsigned int x, y;
	} **sprites;
	unsigned int x, y;
	obstplatid_t id;
};

static void parseLine(ObstaclePlatformHolder::obstplats_map& plats,
 std::string& line)
{
	std::list<std::string> delims;
	delims.push_back(" ");
	Tokeniser tok(line, delims);
	plats_data d;
	
	// Read platform ID
}

static bool shouldParseLine(std::string const& line) { 
	bool result = false;
	if (!Tokeniser::isEmptyLine(line)) {
		if (!Tokeniser::isCommentLine(line))
			result = true;
	}

	return result;
}
