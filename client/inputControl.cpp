#include "inputControl.hpp"

// Implementation headers
#include "pause.hpp"
#include "Ghost.hpp"

typedef GameData::io_bools _bools;
static void handleEvent_keyDown(GameData &d, SDL_Event &event, _bools&);
static void handleEvent_keyUp(GameData &d, SDL_Event &event, _bools&);
static void inputControl(GameData &, _bools &);

static void inputControl(GameData &d, _bools &bools) {
	SDL_Event event;
	if (!SDL_PollEvent(&event))
		return; // no new event

	switch (event.type) {
		case SDL_QUIT :
			bools.exit = true;
			break;
		case SDL_KEYDOWN :
			handleEvent_keyDown(d, event, bools);
			break;
		case SDL_KEYUP :
			handleEvent_keyUp(d, event, bools);
			break;
		default :
			;
	}
} // inputControl

void InputControl::enableGhostInput(Ghost *g) {
	g->setControlled(true);	
	d.ghost.player2 = g;
	d.bools->second_player = true;
}// enableGhostInput

void InputControl::disableGhostInput(void) {
	d.ghost.player2->setControlled(false);
	d.bools->second_player = false;
}// disableGhostInput

void handleEvent_keyDown(GameData &d, SDL_Event &event, _bools &bools) {
	enum ActorMovement::move_t pressed = ActorMovement::NOWHERE, pressed2 = ActorMovement::NOWHERE;
	switch (event.key.keysym.sym) {
		// Pacman actor directive buttons -- notify ActorMovement
		case SDLK_UP : pressed = ActorMovement::UP; break;
		case SDLK_DOWN : pressed = ActorMovement::DOWN; break;
		case SDLK_LEFT : pressed = ActorMovement::LEFT; break;
		case SDLK_RIGHT : pressed = ActorMovement::RIGHT; break;
		// ------------------------------------------------------
		// Ghost actor directive buttons -- notify ActorMovement
		case SDLK_w : pressed2 = ActorMovement::UP; break;
		case SDLK_s : pressed2 = ActorMovement::DOWN; break;
		case SDLK_a : pressed2 = ActorMovement::LEFT; break;
		case SDLK_d : pressed2 = ActorMovement::RIGHT; break;
		// ------------------------------------------------------
		// Exit -- notify and return
		case SDLK_ESCAPE : bools.exit = true; return;
		// ------------------------------------------------------
		// Pause -- notify and return
		case SDLK_p : 
			// do stuff only if not in theatre mode
			if (!bools.theatre_mode) 
				cleanPause(d, bools.paused);
			return;
		// ------------------------------------------------------
		// Enabling second player -- probably temporary
		case SDLK_2 :
	//		enableGhostInput(d.ghost.stalker);
		// ------------------------------------------------------
		default: return ; // nothing
	}

	if (bools.paused) { // paused-mode input processing
	} else if (bools.theatre_mode) { // theatre mode - no movement still
	} else { // running-mode input processing
		d.akmovs[d.pacman]->pressed(pressed, d.currTime);
		if(bools.second_player)
			d.akmovs[d.ghost.player2]->pressed(pressed2, d.currTime);
	}
}

void handleEvent_keyUp(GameData &d, SDL_Event &event, _bools &bools) {
	enum ActorMovement::move_t released = ActorMovement::NOWHERE, released2 = ActorMovement::NOWHERE;
	switch (event.key.keysym.sym) {
		// Pacman actor directive buttons -- notify ActorMovement
		case SDLK_UP : released = ActorMovement::UP; break;
		case SDLK_DOWN : released = ActorMovement::DOWN; break;
		case SDLK_LEFT : released = ActorMovement::LEFT; break;
		case SDLK_RIGHT : released = ActorMovement::RIGHT; break;
		// ------------------------------------------------------
		// Ghost actor directive buttons -- notify ActorMovement
		case SDLK_w : released2 = ActorMovement::UP; break;
		case SDLK_s : released2 = ActorMovement::DOWN; break;
		case SDLK_a : released2 = ActorMovement::LEFT; break;
		case SDLK_d : released2 = ActorMovement::RIGHT; break;
		// ------------------------------------------------------
		default: return ; // nothing
	}

	if (bools.paused) { // paused-mode input processing
	} else if (bools.theatre_mode) { // theatre mode - no movement issue
	} else { // running-mode input processing
		d.akmovs[d.pacman]->released(released, d.currTime);
		if(bools.second_player)
			d.akmovs[d.ghost.player2]->released(released2, d.currTime);
	}
}

InputControl::InputControl(GameData &_d) :
	  d(_d)
	{ }
InputControl::~InputControl(void) { }

InputControl::result_type
InputControl::operator () (argument_type) { inputControl(d, *d.bools); }
