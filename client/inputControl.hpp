/* Handle input events functions. */

#ifndef __inputControl_hpp__
#define __inputControl_hpp__

#include "client.hpp"

class InputControl : public std::unary_function<void, void> {
	GameData &d;

	public:
	void enableGhostInput(Ghost*);
	void disableGhostInput(void);
	
	InputControl(GameData &d);
	~InputControl(void);
	result_type operator()(argument_type);
}; // class InputControl

#endif // __inputControl_hpp__
