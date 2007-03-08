#include "CollisionChecker.hpp"

// Implementation headers
#include "commons.hpp"
using namespace cs454_2006;

CollisionChecker *CollisionChecker::cc = NULL;

CollisionChecker::CollisionChecker(void) :
	  commiter(pairs)
	{ }

void CollisionChecker::Register (Sprite *s1, Sprite *s2) {
	Pair p(s1, s2);

	std::list<Pair>::const_iterator i;
	for(i = pairs.begin(); i != pairs.end(); i++) {
		if(i->first == s1 && i->second == s2)
			return;
		if(i->first == s2 && i->second == s1)
			return;
	}

	queue.push_back(new Op(_register, p));
	return;
}

void CollisionChecker::Cancel (Sprite *s1, Sprite *s2) {
	Pair p(s1, s2);
	queue.push_back(new Op(cancel, p));
	return;
}

void CollisionChecker::Commit(void) {
	std::for_each(queue.begin(), queue.end(), commiter);
	queue.clear();
	return;
}
CollisionChecker::Commiter::result_type
CollisionChecker::Commiter::operator ()(argument_type _p) {
	Op &p = *_p;
	// Show off once again
	void (std::list<Pair>::*op)(Pair const&);
	switch(p.first) { // what operation do we have to perform?
		case _register : // register a pair
			op = &std::list<Pair>::push_back;
			break;
		case cancel :
			op = &std::list<Pair>::remove;
			break;
		default :
			nf(-1, "Illegal program state");
	}
	// Perform the operation
	(pairs.*op)(p.second);
} // Commiter()

// CheckFunctor members
void CollisionChecker::CheckFunctor::operator () (Pair const &p) const {
	if (p.first->CollisionCheck(p.second))
			p.first->NotifyCollision(p.second);
}
// ////////////////////

// Commiter members
CollisionChecker::Commiter::Commiter(std::list<Pair> &_pairs) :
	  pairs(_pairs)
	{ }
CollisionChecker::Commiter::~Commiter(void) { }
// ////////////////////
CollisionChecker *CollisionChecker::Singleton(void) {
	if (!cc)
		cc = new CollisionChecker();
	return cc;
}

void CollisionChecker::Check(void) {
	std::for_each(pairs.begin(), pairs.end(), CheckFunctor());
}
