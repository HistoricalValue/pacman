#include "CollisionChecker.hpp"

CollisionChecker* CollisionChecker::cc = NULL;

CollisionChecker::CollisionChecker(void){}

void CollisionChecker::Register (Sprite* s1, Sprite* s2) {
	Pair p(s1, s2);

	std::list<Pair>::const_iterator i;
	for(i = pairs.begin(); i != pairs.end(); i++) {
		if(i->first == s1 && i->second == s2)
			return;
		if(i->first == s2 && i->second == s1)
			return;
	}
	pairs.push_back(p);
	return;
}

void CollisionChecker::Cancel (Sprite* s1, Sprite* s2) {
	Pair p(s1, s2);
	cancel_queue.push_back(p);
	return;
}

void CollisionChecker::Commit(void) {
	std::list<Pair>::iterator ite;
	for (ite = cancel_queue.begin(); ite != cancel_queue.end(); ite++)
		pairs.remove(*ite);
	return;
}

// CheckFunctor members
void CollisionChecker::CheckFunctor::operator () (Pair const& p) const {
	if (p.first->CollisionCheck(p.second))
			p.first->NotifyCollision(p.second);
}
// ////////////////////

CollisionChecker* CollisionChecker::Singleton(void) {
	if (!cc)
		cc = new CollisionChecker();
	return cc;
}

void CollisionChecker::Check(void) {
	std::for_each(pairs.begin(), pairs.end(), CheckFunctor());
}
