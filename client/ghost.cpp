#include "ghost.hpp"

// Implementation headers
#include "Ghost.hpp"
#include "client.hpp"

void Ghost_collision_callback(Sprite *ghost, Sprite *pacman, void *c) {
	Ghost *gs = dynamic_cast<Ghost*>(ghost);
	if(gs->GetState() == SCARED) { if (c) {
		// It gets called : D
		_gcoca *gkoka = CAST(_gcoca*, c);
		AnimationFilm *retreat_film = gkoka->filmhold->
		 GetFilm("snailyate");
		std::map<GameSprite*, ActorMovement*> &akmovs =
		 *gkoka->akmovs;

		gs->SetState(RETREAT);
		gs->setFilm(retreat_film);
		akmovs[gs]->setDelay(12);
		CollisionChecker::Singleton()->Cancel(gkoka->left_right, gs);	
		CollisionChecker::Singleton()->Register(gkoka->down, gs);

		////testing TODO
		CollisionChecker::Singleton()->Cancel(gkoka->lair, gs);
		
	} else
		db("Warning: Useless pacman-ghost callback");
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
