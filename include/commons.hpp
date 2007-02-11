/* commongs.hpp
 * ************
 *
 * Contains all general purpose functions used by every part
 * of the program as well as common types.
 */

#ifndef __commons_hpp__
#define __commons_hpp__

// System includes
#include <string>
#include <list>
#include <iostream> // for db() macro
// Library includes
#include "SDL/SDL.h"
// Local includes
#include "commons.hpp"
#include "Animator.hpp" // timestamp_t

// ---

#define nf(A,B)	nofail((A),(B),__FILE__,__LINE__)
// Debugging output
#define db(A)	std::cerr<<" *** "<<__FILE__<<':'<<__LINE__<<": "<<(A)<<\
	std::endl;

namespace cs454_2006 {
// Our abstract surface type
typedef SDL_Color Colour;
typedef class Offset off_t;
typedef unsigned int line_t;

// Make sure "value" is 0. Otherwise, print "msg" on stderr.
// "file" and "line" point where the error appeared and exit the program.
void nofail(int value, char const* msg, char const* file, line_t line);

// blit src onto (x,y) of dst.
void blit(SDL_Surface* src, SDL_Surface* dst, off_t x, off_t y);
// blit src onto the center of dst
void blit_centre(SDL_Surface* src, SDL_Surface* dst);

template <class T>
T& min(T const& a, T const& b) { return b < a ? b : a; }

template <class T>
T& max(T const& a, T const& b) { return b > a ? b : a; }

// offset class
class Offset {
	unsigned short v;
	public :
	static long const max_val;
	Offset(long const _v) : v(min<long const>(max_val, _v)) {} ;
	~Offset(void) {};
	Offset& operator+(Offset& o);
	Offset& operator=(Offset& o);
	operator unsigned short();
};

// Tokeniser \m/ 
// NOTICE that upon creating (constructor call) the first token will
// be read (as it the ++ operator had been used).
class Tokeniser {
	char *line, *original;
	std::list<std::string> delims;
	std::string* ctok; // current token
	protected :
	void advance(void);
	public :
	operator std::string*(void);
	std::string* operator ->(void);
	Tokeniser& operator ++(void);
	static bool isEmptyLine(std::string const& line);
	static bool isCommentLine(std::string const& line);
	Tokeniser(std::string& line, std::list<std::string>& delims);
	~Tokeniser(void);
}; // Tokeniser

// get current system time in miliseconds
timestamp_t getTimestamp(void);

// C++ string into long
long cppstrtol(std::string& str, int base);

// Returns 0 if the value is not 0. -1 otherwise.
int ensureTrue(int value);


// After move call and return types.
// Used by animators to make checks after every animation single stepping
// progression.
struct amc_t {
	virtual int operator () (Animator*) const = 0;
	virtual ~amc_t(void);
};

// Game data
struct GameData;
extern struct GameData* getGameData(void);

// Get current time
extern timestamp_t getCurrentTime(void);
} // namespace cs454_2006

#endif // __commons_hpp__
