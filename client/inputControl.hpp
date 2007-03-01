/* Handle input events functions. */

#ifndef __inputControl_hpp__
#define __inputControl_hpp__

#include "client.hpp"
struct _bools {
	bool &exit, &paused;
	_bools(bool &exit, bool &paused);
};
extern void inputControl(GameData &, _bools &);
#endif // __inputControl_hpp__
