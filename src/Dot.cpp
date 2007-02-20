#include "Dot.hpp"

uint8_t Dot::getNumberOfRepeats(void) {
	return number_of_repeats;
}

void Dot::setNumberOfRepeats(uint8_t numreps) {
	repeats = numreps;
}

void Dot::operator++(void) {
	--repeats;
}

void Dot::resetNumberOfRepeats(void) {
	repeats = number_of_repeats;
}

Dot::Dot(int x, int y, AnimationFilm *film, spriteid_t id, uint8_t numr) :
	GameSprite(x, y, film, id),
	number_of_repeats(numr),
	repeats(number_of_repeats)
{ }

bool Dot::animationIsFinished(void) {
	return !repeats;
}
