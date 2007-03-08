#ifndef _COLLISIONCHECKER_HPP_
#define _COLLISIONCHECKER_HPP_

#include <list>
#include "Sprite.hpp"
#include <iostream>

class CollisionChecker {
	static CollisionChecker *cc;
	
	typedef std::pair<Sprite*, Sprite*> Pair;
	std::list<Pair> pairs;
	typedef enum _op_t {_register, cancel} op_t;
	typedef std::pair<op_t, Pair> Op;
	std::list<Op*> queue;

	CollisionChecker(void);
	
	struct CheckFunctor : public std::unary_function<const Pair&, void>{
		result_type operator()(argument_type) const;
	};
	struct Commiter : public std::unary_function<Op*, void> {
		result_type operator ()(argument_type);
		Commiter(std::list<Pair> &pairs);
		~Commiter(void);
		private :
		std::list<Pair> &pairs;
	} commiter;
	
	public:
	static CollisionChecker *Singleton(void);
	void Register (Sprite *callbacker, Sprite *stooker);
	void Cancel (Sprite *callbacker, Sprite *stooker);
	void Check (void);
	void Commit(void);
};

#endif
