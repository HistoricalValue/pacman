#include "second_player.hpp"

void enableGhostInput(Ghosts &ghost, GameData::io_bools &iob) {
	static uint8_t ghost_select = 0;
	switch (ghost_select) {
		case 0: ghost.player2 = ghost.stalker; break;
		case 1: ghost.player2 = ghost.kieken; break;
		case 2: ghost.player2 = ghost.random; break;
		case 3: ghost.player2 = ghost.retard; break;
		default : nf(-1, "Illegal program state"); break;
	}
	ghost_select = ghost_select > 3 ? 0 : ghost_select + 1;
	ghost.player2->setControlled(true);
	iob.second_player = true;
}// enableGhostInput

void disableGhostInput(Ghosts &ghost, GameData::io_bools &iob) {
	ghost.player2->setControlled(false);
	iob.second_player = false;
}// disableGhostInput

