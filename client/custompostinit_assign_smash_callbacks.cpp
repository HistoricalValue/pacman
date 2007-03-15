#include "custompostinit_assign_smash_callbacks.hpp"
#include "death_pacman.hpp"

CPI_DEFINE(custompostinit_assign_smash_callbacks) {
	_gcoca *gkoka = getacoca(d, gd);

	// Assign pacman shmash callback
	gd.pacman->SetOnSmashed(
	 pacman_death_by_smash_callback,
	 new _shca( gkoka )
	);

	// Assign ghosts shmash callbacks
	gd.ghost.stalker->SetOnSmashed(
	 ghost_death_by_smash,
	 gkoka);
	gd.ghost.kieken->SetOnSmashed(
	 ghost_death_by_smash,
	 gkoka);
	gd.ghost.random->SetOnSmashed(
	 ghost_death_by_smash,
	 gkoka);
	gd.ghost.retard->SetOnSmashed(
	 ghost_death_by_smash,
	 gkoka);
} // custompostinit_assign_smash_callbacks
