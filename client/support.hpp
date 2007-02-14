/* Various support functions and classes/structures,
 * such as callbacks, used during the game.
 */

#ifndef __callbacks_hpp__
#define __callbacks_hpp__

#include "client.hpp"
#include "commons.hpp"

struct Callbacks {
	struct amc : public cs454_2006::amc_t {
		int operator() (Animator*) const; 
		amc(CollisionChecker*); ~amc(void);
		private :
		CollisionChecker *cc;
	};
	Callbacks(void); ~Callbacks(void);
}; // struct Callbacks

extern void cleanup(void);

#endif // __callbacks_hpp__
