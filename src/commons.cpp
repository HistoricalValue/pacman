/* commons.cpp
 * ***********
 *
 * Implementation of the commons header
 */

#include "commons.hpp"
#include <iostream>
#include <time.h>	//  
#include <sys/time.h>	// for system time access in mili(micro)seconds
#include <ctype.h>

namespace cs454_2006 {

void nofail(int v, char const* msg, char const* file, line_t line)
{
	if (v) {
		std::cerr << std::endl << " *** Failure: " << file <<
		 ":" << line << ":(" << v << "): " << msg <<
		 std::endl;
		exit(v);
	}
} // nofail ()

void blit(SDL_Surface* src, SDL_Surface* dst, off_t x, off_t y)
{
	std::cerr << "Blitting " << src << " onto " <<
	 dst << "(" << x << "," << y << ")" << std::endl;
	SDL_Rect r = {x, y, 0, 0};
	nf(SDL_BlitSurface(src, NULL, dst, &r),
	 SDL_GetError());
} // blit()

void blit_centre(SDL_Surface* src, SDL_Surface* dst)
{
	SDL_Rect r = {
	 (dst->w - src->w) >> 1,
	 (dst->h - src->h) >> 1,
	 0, 0};
	std::cerr << "Blitting " << src << " onto " <<
	 dst << "(" << r.x << "," << r.y << ")" << std::endl;

	nf(SDL_BlitSurface(src, NULL, dst, &r),
	 SDL_GetError());
}

Offset::operator unsigned short () { return v; }
long const Offset::max_val = (0x00000000ffffl);

// Tokeniser stuff
Tokeniser::Tokeniser(std::string& l, std::list<std::string>& ds) :
	delims(ds), ctok(NULL)
{
	line = static_cast<char*>(malloc(l.length() + 1));
	nf(!line, "Could not allocate memory");
	original = strcpy(line, l.c_str()); // pointer used to free mem
	advance();
} // constructor

void Tokeniser::advance(void) {
	std::list<std::string>::const_iterator ite = delims.begin();
	ctok = NULL;
	for (; ite != delims.end(); ite++) {
		char *result = strstr(line, ite->c_str());
		if (result) { // delimiter was found
			// create token
			*result = '\0';
			ctok = new std::string(line);
			// repair line-string
			*result = ite->at(0);
			// update where to begin search next time
			line = result + ite->length();
			// enough searching
			break;
		} else { // delimiter not found
			// Keep searching...
		}
	}

	// If a delimiter was found, ctok now holds a token.
	// Otherwise it is NULL.
	// Same goes for last_pos. Next time search starts from last_pos.
	
	// But if no delimiter wass found and the EOS is not reached yet,
	// the last piece must be returned.
	if (!ctok && *line) { // no result and line is not pointing to EOS
		ctok = new std::string(line);
		// mark line pointer as if it had reached end
		*line = 0;
	}
} // advance

Tokeniser& Tokeniser::operator ++(void) {
	advance();
	return *this;
} // Tokeniser++

Tokeniser::operator std::string*(void) { return ctok; }
std::string* Tokeniser::operator -> (void) { return ctok; }

Tokeniser::~Tokeniser(void) {
	delete original;
} // destructor

bool Tokeniser::isEmptyLine(std::string& line) {
	bool result = true;
	
	std::string::const_iterator ite;
	for (ite = line.begin(); ite != line.end(); ite++)
		if ( (result = isspace(*ite)) == false)
			break;

	return result;
} // isEmptyLine
// End Tokeniser stuff //////////////////////


timestamp_t getTimestamp(void) {
	return SDL_GetTicks();
//	timeval t;
//	nf(gettimeofday(&t, NULL), "Could not get current system time.");
//	// tv_usec is in microseconds, too much precision.
//	// we keep the milisecond part, discard the largest thousands
//	// of seconds, and merge them.
//	return
//	 // lose second precision up to one decade more than required to
//	 // avoid data overflow.
//	 (t.tv_sec % 1000000) * 1000
//	 + (t.tv_usec / 1000);
} // getTimestamp

long cppstrtol(std::string& s, int b) { return strtol(s.c_str(), NULL, b); }

int ensureTrue(int value) { return value ? 0 : -1; }

amc_t::~amc_t(void) { }
} // namespace cs454_2006
