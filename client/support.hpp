/* Various support functions and classes/structures,
 * such as callbacks, used during the game.
 */

#ifndef __callbacks_hpp__
#define __callbacks_hpp__

#include "client.hpp"
#include "commons.hpp"

struct _cocaclo {
	std::list<ActorMovement*> informees; // act-movs to be informed
}; // struct _cocaclo

struct Callbacks {
	amc_t &get_amc(void);
	Sprite::CollisionCallback get_coca(void);
	void set_cocaclo(_cocaclo*); // set collision callback closure
	_cocaclo *get_cocaclo(void); // get collision callback closure

	Callbacks(
	 CollisionChecker*,
	 Sprite::CollisionCallback);
	~Callbacks(void);
	private :
	struct _amc : public cs454_2006::amc_t {
		int operator() (Animator*) const; 
		_amc(void); ~_amc(void);
	};
	CollisionChecker *cc;
	_amc amc;
	Sprite::CollisionCallback coca;
	_cocaclo *cocaclo;
}; // struct Callbacks

extern void collision_callback(Sprite*, Sprite*, void *c = NULL);
extern void cleanup(void);

#endif // __callbacks_hpp__
