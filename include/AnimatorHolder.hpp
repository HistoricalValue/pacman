#ifndef _ANIMATORHOLDER_HPP_
#define _ANIMATORHOLDER_HPP_

#include <list>
#include <functional>
#include <algorithm>

#include "commons.hpp"
#include "Animator.hpp"

using namespace cs454_2006;

class AnimatorHolder {
	private :
	static std::list<Animator*> running, suspended;
	// Progresses the given animator
	class ProgressFunctor : public std::unary_function<Animator*, void>
	{
		timestamp_t t;
		public: 
		void operator()(Animator* a) const;
		ProgressFunctor (timestamp_t _t);
	};
	// Timeshifts the given Animator
	class TimeshiftFunctor : public std::unary_function<Animator*, void>
	{
		timestamp_t t;
		public :
		void operator()(Animator* a) const;
		TimeshiftFunctor (timestamp_t _t);
	};
	static amc_t const* amc;
	public:
	static void Register (Animator* a);
	static void Cancel (Animator* a);
	static void MarkAsRunning (Animator* a);
	static void MarkAsSuspended (Animator* a);
	static void Progress (timestamp_t currTime);
	static void TimeShift (timestamp_t currTime);
	static amc_t const* getAfterMoveCall(void);
	static void setAfterMoveCall(amc_t const*);
};

#endif
