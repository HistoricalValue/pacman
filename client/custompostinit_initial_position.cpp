#include "CustomPostinit_Commons.hpp"

struct PositionSave : public std::unary_function<GameSprite*, void> {
	result_type operator()(argument_type);
	PositionSave(std::map<GameSprite*, SDL_Rect> &);
	private :
	std::map<GameSprite*, SDL_Rect> &p;
}; // struct PositionSave

CPI_DEFINE(custompostinit_initial_position) {
	std::for_each(gd.sss.begin(), gd.sss.end(),
	 PositionSave(gd.custom->initpos));
	db("Initial positions -- saved");
} // custompostinit_inital_position

PositionSave::PositionSave(std::map<GameSprite*, SDL_Rect> &_p) : 
	p(_p) { }

PositionSave::result_type
PositionSave::operator()(argument_type ss) {
	// ss = special sprite (actor)
	p.insert(
	 *new std::pair<GameSprite *const, SDL_Rect>(ss, *new SDL_Rect));
	p[ss].x = ss->GetX();
	p[ss].y = ss->GetY();
} // PositionSave()
