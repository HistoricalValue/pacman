#include "custompostinit_assign_smash_callbacks.hpp"
#include "death_pacman.hpp"

CPI_DEFINE(custompostinit_assign_smash_callbacks) {
	// Assign pacman shmash callback
	gd.pacman->SetOnSmashed(
	 pacman_death_by_smash_callback,
	 new _shca(
	  d.cc)
	);
} // custompostinit_assign_smash_callbacks
