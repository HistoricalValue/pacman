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
	static std::list<Animator*> running, suspended, x_running;
	// Progresses the given animator
	class ProgressFunctor : public std::unary_function<Animator*, void>
	{
		timestamp_t t;
		public: 
		void operator()(Animator *a) const;
		ProgressFunctor (timestamp_t _t);
	};
	// Timeshifts the given Animator
	class TimeshiftFunctor : public std::unary_function<Animator*, void>
	{
		timestamp_t t;
		public :
		void operator()(Animator *a) const;
		TimeshiftFunctor (timestamp_t _t);
	};
<<<<<<< TREE
	// Suspender/Resumer
	class _susres : public std::unary_function<Animator*, void> {
		public :
		enum mode {suspend, resume};
		result_type operator()(argument_type);
		_susres &operator[](enum mode);
		_susres &operator=(timestamp_t);
		_susres(std::list<Animator*> &_r, std::list<Animator*> &_x);
		void setMode(enum mode);
		private :
		std::list<Animator*> &r, &x;
		enum mode m;
		timestamp_t t;
	};
	static _susres susres;
	static amc_t const *amc;
=======
	public :
	// Suspender/Resumer
	class _susres : public std::unary_function<Animator*, void> {
		public :
		enum mode {suspend, resume};
		result_type operator()(argument_type);
		_susres &operator[](enum mode);
		_susres &operator=(timestamp_t);
		_susres(std::list<Animator*> &_r, std::list<Animator*> &_x);
		void setMode(enum mode);
		private :
		std::list<Animator*> &r, &x;
		enum mode m;
		timestamp_t t;
	};
	private :
	static _susres susres;
	static amc_t const *amc;
>>>>>>> MERGE-SOURCE
	public:
	static void Register (Animator *a);
	static void Cancel (Animator *a);
	static void MarkAsRunning (Animator *a);
	static void MarkAsSuspended (Animator *a);
	static void Progress (timestamp_t currTime);
	static void TimeShift (timestamp_t currTime);
	static amc_t const *getAfterMoveCall(void);
	static void setAfterMoveCall(amc_t const*);
	static std::list<Animator*> getRunning(void);
	static std::list<Animator*> getSuspended(void);
	// Suspends all running animators, which can be later on be
	// resumed through resumeAllExRunning()
	static void suspendAllRunning(timestamp_t);
	static void resumeAllExRunning(timestamp_t);
};

#endif
