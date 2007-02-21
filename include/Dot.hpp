/* Dot.hpp
 *
 * Dot sprite header. Keeps information about the number of
 * repeats a dot animation should run.
 */

#ifndef __Dot_hpp__
#define __Dot_hpp__

#include "commons.hpp"
#include "GameSprite.hpp"

class Dot : public GameSprite {
	public :
	uint8_t getNumberOfRepeats(void);
	void setNumberOfRepeats(uint8_t numreps);
	void operator++(void);
	void resetNumberOfRepeats(void);
	bool animationIsFinished(void);
	Dot(int x, int y, AnimationFilm *film, spriteid_t id, uint8_t numr);
	static
	void collisionCallback(Sprite*, Sprite*, void *c = CAST(void*,0));
	struct _coca; // collision closure
	private :
	uint8_t const number_of_repeats;
	uint8_t repeats;
}; // class Dot

#endif // __Dot_hpp__
