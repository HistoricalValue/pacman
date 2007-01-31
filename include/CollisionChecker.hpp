#ifndef _COLLISIONCHECKER_HPP_
#define _COLLISIONCHECKER_HPP_

#include <list>
#include "Sprite.hpp"
#include <iostream>

class CollisionChecker {
	static CollisionChecker *cc;
	
	typedef std::pair<Sprite*, Sprite*> Pair;
	std::list<Pair> pairs;

	CollisionChecker(void);
	
	struct CheckFunctor : public std::unary_function<Pair, void> {
		void operator()(const Pair& p) const;
	};
	
	public:
	static CollisionChecker* Singleton(void);
	void Register (Sprite* s1, Sprite* s2);
	void Cancel (Sprite* s1, Sprite* s2);
	void Check (void);
};

#endif
