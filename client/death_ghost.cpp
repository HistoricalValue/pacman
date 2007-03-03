#include "death_ghost.hpp"
#include "SoundManager.hpp"

void ghost_death_callback(Ghost *g, GameSprite *p, _gcoca *gkoka) {
  SoundManager::Singleton()->PlayEffect(6, GHOST);
}
