#include "ghost.hpp"

// Implementation headers
#include "Ghost.hpp"
#include "client.hpp"
#include "death_ghost.hpp"
#include "commons.hpp"
#include "SoundManager.hpp"

void Ghost_collision_callback(Sprite *ghost, Sprite *pacman, void *c) {
	if (!c) {
		db("Warning: Useless pacman-ghost callback");
		return;
	}
	Ghost *gs = dynamic_cast<Ghost*>(ghost);
	nf(!gs, "Sprite supposed to be ghost is not a ghost sprite.");
	GameSprite *pac = DYNCAST(GameSprite*, pacman);
	nf(!pac, "Pacman is not a GameSprite.");
	_gcoca *gkoka = CAST(_gcoca*, c);
	if(gs->GetState() == SCARED) {
		AnimationFilm *retreat_film = gkoka->filmhold->
		 GetFilm("snailyate");
		std::map<GameSprite*, ActorMovement*> &akmovs =
		 *gkoka->akmovs;

		gs->SetState(RETREAT);
		gs->setFilm(retreat_film);
		akmovs[gs]->setDelay(12);
		CollisionChecker::Singleton()->Cancel(gkoka->left_right, gs);	
		CollisionChecker::Singleton()->Register(gkoka->down, gs);
		SoundManager::Singleton()->PlayEffect(6, GHOST);
		////testing TODO
		CollisionChecker::Singleton()->Cancel(gkoka->lair, gs);
	} else if (gs->GetState() == NORMAL) {
		// ghost is not scared -- it eats pacman instead
		// redirect to death_ handlers
		ghost_death_callback(gs, pac, gkoka);
	} else { // ghost is eatten
		// do nothing
	}
} // collision_callback

// Callback which happens when a ghost is found back into the lair.
// It sets the eatten ghost back to its normal state.
void ghost_uneating_callback(Sprite *waypoint, Sprite *_ghost, void *c) {
	Ghost *gs = dynamic_cast<Ghost*>(_ghost);
	if(gs->GetState() == RETREAT) if(c){
		AnimationFilm *film;
		_gcoca *gkoka = CAST(_gcoca*, c);
		if(gs == gkoka->ghost->stalker)
			film = gkoka->filmhold->GetFilm("snaily");
		else if(gs == gkoka->ghost->random)
			film = gkoka->filmhold->GetFilm("snailyd");
		else if(gs == gkoka->ghost->retard)
			film = gkoka->filmhold->GetFilm("snailyb");
		else film = gkoka->filmhold->GetFilm("snailyl");
		gs->SetState(NORMAL);
		gs->setFilm(film);
		(*gkoka->akmovs)[gs]->setDelay(15);
		(*gkoka->akmovs)[gs]->pressed(ActorMovement::UP, getCurrentTime());
		CollisionChecker::Singleton()->Cancel(gkoka->down, gs);	
		CollisionChecker::Singleton()->Register(gkoka->left_right, gs);

      	}
	
} // ghost_uneating_callback
