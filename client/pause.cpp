#include "pause.hpp"

#include "AnimatorHolder.hpp"

void cleanPause(GameData &d, bool &paused) {
	// Set paused state opposite than before
	paused = !paused;
	
	// Suspend all running animators
} // cleanPause
