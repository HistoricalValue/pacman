#include "sakutest.hpp"

namespace sakutest {
using namespace cs454_2006;

void handleEvent(data& d, SDL_Event& event) {
	switch (event.type) {
		case SDL_QUIT :
			exit(0);
			break;
		case SDL_KEYDOWN :
			handleEvent_keyDown(d, event);
			break;
		case SDL_KEYUP :
			handleEvent_keyUp(d, event);
			break;
		default :
			;
	}
}

void handleEvent_keyDown(data& d, SDL_Event& event) {
	enum ActorMovement::move_t pressed;
	switch (event.key.keysym.sym) {
		case SDLK_UP : pressed = ActorMovement::UP; break;
		case SDLK_DOWN : pressed = ActorMovement::DOWN; break;
		case SDLK_LEFT : pressed = ActorMovement::LEFT; break;
		case SDLK_RIGHT : pressed = ActorMovement::RIGHT; break;
		case SDLK_ESCAPE : exit(0);
		default: return ; // nothing
	}
	d.pacmov->pressed(pressed, d.currTime);
}

void handleEvent_keyUp(data& d, SDL_Event& event) {
	enum ActorMovement::move_t released;
	switch (event.key.keysym.sym) {
		case SDLK_UP : released = ActorMovement::UP; break;
		case SDLK_DOWN : released = ActorMovement::DOWN; break;
		case SDLK_LEFT : released = ActorMovement::LEFT; break;
		case SDLK_RIGHT : released = ActorMovement::RIGHT; break;
		case SDLK_ESCAPE : exit(0);
		default: return ; // nothing
	}
	d.pacmov->released(released, d.currTime);
}

} // namespace sakutest
