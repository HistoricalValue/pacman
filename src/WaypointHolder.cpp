#include "WaypointHolder.hpp"
#include <fstream>
#include "commons.hpp"
using namespace cs454_2006;

static void parseFile(WaypointHolder* self, std::string const&);
static bool shouldParse(std::string const& line);
static void parseLine(WaypointHolder*, std::string&,
 std::list<std::string>& delims);

WaypointHolder::WaypointHolder(std::string const& cf):bug(NULL) {
	parseFile(this, cf);
} // constructor

static void parseFile(WaypointHolder* self, std::string const& cf)
{
	std::ifstream fin(cf.c_str());
	if (!fin) {
		std::string msg("Could not open file : ");
		nf(-1, msg.append(cf).c_str());
	}
	std::string line;
	std::list<std::string> delims;
	delims.push_back(" ");
	
	while (!fin.eof()) {
		getline(fin, line);
		if (shouldParse(line))
			parseLine(self, line, delims);
	}
} // parseLine

static bool shouldParse(std::string const& line) {
	return !Tokeniser::isEmptyLine(line) &&
	 !Tokeniser::isCommentLine(line);
} // shouldParse 

struct waydata {
	waypointid_t id;
	int x, y;
	unsigned char up, right, down, left;
};
#define conftopx(A) ((A)<<3)
static void parseLine(WaypointHolder* self, std::string& line,
 std::list<std::string>& delims)
{
	Tokeniser tok(line, delims);
	waydata d;

	// read id
	d.id = cppstrtol(*tok, 10);
	// read x and y
	d.x = conftopx(cppstrtol(*++tok, 10));
	d.y = conftopx(cppstrtol(*++tok, 10));
	// read up, right, down, left
	d.up = cppstrtol(*++tok, 10);
	d.right = cppstrtol(*++tok, 10);
	d.down = cppstrtol(*++tok, 10);
	d.left = cppstrtol(*++tok, 10);

	Waypoint *n00b = NULL;
	self->addWaypoint(n00b = new Waypoint(
	   d.x
	 , d.y
	 , d.up
	 , d.down
	 , d.left
	 , d.right
	 , d.id )
	);
	std::cerr << *n00b <<std::endl;
} // parseLine

void WaypointHolder::addWaypoint(Waypoint const* w) {
	waypoints.push_back(w);
} // addWaypoint

void WaypointHolder::display(SDL_Surface* dst) {
	std::list<Waypoint const*>::iterator ite;
	for (ite = waypoints.begin(); ite != waypoints.end(); ite++) {
		SDL_Rect dstpoint;
		dstpoint.x = (*ite)->GetX();
		dstpoint.y = (*ite)->GetY();
		SDL_BlitSurface(bug, NULL, dst, &dstpoint);
	}
} // display

void WaypointHolder::setBug(SDL_Surface* _bug) {
	bug = _bug;
} // setBug
