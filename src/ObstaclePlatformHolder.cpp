#include <fstream>
#include "ObstaclePlatformHolder.hpp"
#include "commons.hpp"
using namespace cs454_2006;

static bool shouldParseLine(std::string const& line);
static void parseLine(ObstaclePlatformHolder::obstplat_list& plats,
 std::string const& line);

ObstaclePlatformHolder::ObstaclePlatformHolder(
 std::string const& cf, SpriteHolder* sh)
{
	std::list<std::string> delims;
	delims.push_back(" ");
	std::string line;
	std::ifstream* fin = new std::ifstream(cf.c_str(), std::ios::in);

	nf(!fin, "Could not load Obstacle Platform config file");

	while (!fin->eof()) {
		getline(*fin, line);
		if (shouldParseLine(line))
			parseLine(plats, line);
	}
}

static void parseLine(ObstaclePlatformHolder::obstplat_list& plats,
 std::string const& line)
{
	std::cerr<<line<<" (parse)"<<std::endl;
}

static bool shouldParseLine(std::string const& line) { 
	bool result = false;
	if (!Tokeniser::isEmptyLine(line)) {
		if (!Tokeniser::isCommentLine(line))
			result = true;
	}

	return result;
}
