// system includes
#include <fstream>
#include <iostream>
#include <map>
// local includes
#include "AnimationHolder.hpp"
#include "commons.hpp"
// namespace
using namespace cs454_2006;
// definitions
struct mv_data {
	animid_t animid;
	offset_t dx, dy;
	delay_t delay;
	bool continuous;
};
struct fr_data : public mv_data {
	frame_t start, end;
};
static void parseConfigFile(const char*, std::list<MovingAnimation*>&,
 std::list<FrameRangeAnimation*>&);
static bool shouldParse(std::string&);
static void parseLine(Tokeniser**, std::string*, std::list<std::string>*,
 std::list<MovingAnimation*>&, std::list<FrameRangeAnimation*>&);
static void parseMovingAnimationLine(Tokeniser*, mv_data& d);
static void parseFrameRangeAnimationLine(Tokeniser*, fr_data& d);

// implementations
MovingAnimationList const&
AnimationHolder::getMovingAnimations(void) const { return mv_anims; }

FrameRangeAnimationList const&
AnimationHolder::getFrameRangeAnimations(void) const { return fr_anims; }

AnimationHolder::AnimationHolder(std::string const& config_f) {
	parseConfigFile(config_f.c_str(), mv_anims, fr_anims);
} // constructor

static void parseConfigFile(const char* file,
 std::list<MovingAnimation*>& mv_anims,
 std::list<FrameRangeAnimation*>& fr_anims)
{
	// open input stream to the configuration file
	std::ifstream fin(file, std::ios::in);
	if (!fin)
		nf(-1, "Could not open config file for reading");

	// set up
	const char space = ' ';
	std::string buf(1<<10, space);
	std::list<std::string> delims;
	delims.push_back(" ");
	Tokeniser* tok = NULL;
	
	// while not at EOF
	while (!fin.eof()) {
		getline(fin, buf);
		if (shouldParse(buf))
			parseLine(&tok, &buf, &delims, mv_anims, fr_anims);
	}
} // parserConfigFile

AnimationHolder::~AnimationHolder(void) { } // destructor`

static bool shouldParse(std::string& line) {
	bool result = false;
	if (!Tokeniser::isEmptyLine(line))
		result = line.at(0) != '#';
	return result;

} // shouldParse

static void parseLine(Tokeniser** tokptr, std::string* line,
 std::list<std::string>* delims, std::list<MovingAnimation*>& mv_anims,
 std::list<FrameRangeAnimation*>& fr_anims)
{
	// types of animations and the strings associated
	static std::string const
	 MOVING_ANIMATION("mv"),
	 FRAME_RANGE_ANIMATION("fr");
	// create the tokeniser with input line and delimiters
	*tokptr = new Tokeniser(*line, *delims);
	// local ptr copy for convenience
	Tokeniser* tok = *tokptr;	

	// find out type and create appropriate tmp data holder
	if (**tok == MOVING_ANIMATION) {
		mv_data d;
		parseMovingAnimationLine(tok, d);
		MovingAnimation* mv_anim;
		mv_anims.push_back( mv_anim = new MovingAnimation( d.dx,
		 d.dy, d.delay, d.continuous, d.animid) );
		db("Created moving animation:");
		std::cerr << *mv_anim << std::endl;
	} else if (**tok == FRAME_RANGE_ANIMATION) {
		fr_data d;
		parseFrameRangeAnimationLine(tok, d);
		FrameRangeAnimation* fr_anim;
		fr_anims.push_back( fr_anim = new FrameRangeAnimation(
		 d.start, d.end, d.dx, d.dy, d.delay, d.continuous,
		 d.animid) );
		db("Created frame range animation:");
		std::cerr << *fr_anim << std::endl;
	} else
		nf(-1, "Illegal program state");
} // parseLine

static void parseMovingAnimationLine(Tokeniser* tok, mv_data& d) {
	d.animid = cppstrtol(*++*tok, 10);
	d.dx = cppstrtol(*++*tok, 10);
	d.dy = cppstrtol(*++*tok, 10);
	d.delay = cppstrtol(*++*tok, 10);
	d.continuous = cppstrtol(*++*tok, 10);
} // parseMovingAnimationLine

static void parseFrameRangeAnimationLine(Tokeniser* tok, fr_data& d) {
	parseMovingAnimationLine(tok, d);
	d.start = cppstrtol(*++*tok, 10);
	d.end = cppstrtol(*++*tok, 10);
} // parseFrameRangeAnimationLine

Animation* AnimationHolder::getAnimation(animid_t id) const {
	MovingAnimation* result = getFrameRangeAnimation(id);
	if (!result)
		result = getMovingAnimation(id);
	return result;
} // getAnimation

MovingAnimation* AnimationHolder::getMovingAnimation(animid_t id) const {
	MovingAnimationList::const_iterator ite;
	for (ite = mv_anims.begin(); ite != mv_anims.end(); ite++)
		if ((*ite)->GetId() == id)
			return *ite;
	return NULL;
} // getMovingAnimation

FrameRangeAnimation* AnimationHolder::getFrameRangeAnimation(animid_t id)
 const
{
	FrameRangeAnimationList::const_iterator ite;
	for (ite = fr_anims.begin(); ite != fr_anims.end(); ite++)
		if ((*ite)->GetId() == id)
			return *ite;
	return NULL;
} // getFrameRangeAnimation
