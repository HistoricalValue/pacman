#include "ghost.hpp"

// Implementation headers
#include "Ghost.hpp"
#include "client.hpp"
#include "death_pacman.hpp"
#include "commons.hpp"
#include "SoundManager.hpp"
#include "inputControl.hpp"

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

		// Cancel the left-right waypoint and enable the
		// downward one so that the snails get back in the
		// lair.
		gkoka->cc->Cancel(gkoka->left_right, gs);	
		gkoka->cc->Register(gkoka->down, gs);
		SoundManager::Singleton()->PlayEffect(6, GHOST);
		// Disabling possible second player input
	} else if (gs->GetState() == NORMAL) {
		// ghost is not scared -- it eats pacman instead
		// redirect to death_ handlers
		pacman_death_by_ghost_callback(gs, pac, gkoka);
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
		(*gkoka->akmovs)[gs]->
		 pressed(ActorMovement::UP, getCurrentTime());
		gkoka->cc->Cancel(gkoka->down, gs);	
		gkoka->cc->Register(gkoka->left_right, gs);
      	}
	
} // ghost_uneating_callback

_gcoca *getacoca(InitData &d, GameData &r) {
	_gcoca *gkoka = new _gcoca;
	gkoka->cc = r.cc; // the collision checker
	gkoka->akmovs = &r.akmovs; // the ActorMovement instances
	gkoka->ghost = // pointers to the ghosts GameSprite instances
	 &r.ghost; 
	gkoka->filmhold = r.animdata->filmhold; // the film holder
	gkoka->animhold = r.animdata->animhold; // the animation holder
	gkoka->sch = r.sch; // the scheduler
	gkoka->left_right = // waypoint that sends snails away from the lair
	 r.animdata->wayhold->getWaypoint(d.weeds[d.TM]);
	gkoka->down = // a waypoint that sends snails in the lair
	 r.animdata->wayhold->getWaypoint(d.weeds[d.TI]);
	gkoka->lair = // a waypoint that is inside the lair
	 r.animdata->wayhold->getWaypoint(WAYPOINT_LAIR);
	gkoka->initpos = // the initial positions of the special sprites
	 &r.custom->initpos;
	gkoka->gs = r.stats; // game status manager instance
	gkoka->theatre_mode = &r.bools->theatre_mode; // IO status flag

	return gkoka;
}

