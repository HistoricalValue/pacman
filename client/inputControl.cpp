#include "inputControl.hpp"

void handleEvent_keyDown(GameData &d, SDL_Event& event, bool*);
void handleEvent_keyUp(GameData &d, SDL_Event& event, bool*);

void inputControl(GameData &d, bool *exit) {
	SDL_Event event;
	if (!SDL_PollEvent(&event))
		return; // no new event

	switch (event.type) {
		case SDL_QUIT :
			*exit = true;
			break;
		case SDL_KEYDOWN :
			handleEvent_keyDown(d, event, exit);
			break;
		case SDL_KEYUP :
			handleEvent_keyUp(d, event, exit);
			break;
		default :
			;
	}
} // inputControl

void handleEvent_keyDown(GameData &d, SDL_Event& event, bool *exit) {
	enum ActorMovement::move_t pressed;
	switch (event.key.keysym.sym) {
		case SDLK_UP : pressed = ActorMovement::UP; break;
		case SDLK_DOWN : pressed = ActorMovement::DOWN; break;
		case SDLK_LEFT : pressed = ActorMovement::LEFT; break;
		case SDLK_RIGHT : pressed = ActorMovement::RIGHT; break;
		case SDLK_ESCAPE : *exit = true;
		default: return ; // nothing
	}
	d.akmovs[d.pacman]->pressed(pressed, d.currTime);
//	d.akmovs[d.ghost.stalker]->pressed(pressed, d.currTime);
}

void handleEvent_keyUp(GameData &d, SDL_Event& event, bool *exit) {
	enum ActorMovement::move_t released;
	switch (event.key.keysym.sym) {
		case SDLK_UP : released = ActorMovement::UP; break;
		case SDLK_DOWN : released = ActorMovement::DOWN; break;
		case SDLK_LEFT : released = ActorMovement::LEFT; break;
		case SDLK_RIGHT : released = ActorMovement::RIGHT; break;
		case SDLK_ESCAPE : *exit = true;
		default: return ; // nothing
	}
	d.akmovs[d.pacman]->released(released, d.currTime);
//	d.akmovs[d.ghost.stalker]->released(released, d.currTime);
}
