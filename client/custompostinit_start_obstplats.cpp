#include "CustomPostinit_Commons.hpp"
#include "ObstaclePlatformAnimator.hpp"
#include <algorithm>

template <class _Ta = bool, class _Tb = int, class _Tc = int>
struct _three {
	_Ta a;
	_Tb b;
	_Tc c;
	_three(_Ta _a, _Tb _b, _Tc _c) : a(_a), b(_b), c(_c) { }
};

struct obstplat_starter {
	void operator ()(_three<> &);
	obstplat_starter(GameData &gd, InitData &d);
	private :
	GameData &gd;
	InitData &d;
};

static void obstplat_anim_coca(Animator *_animator, void *c) {
	int &repeats = *CAST(int*,c);
	if (repeats++ > 64) {
		ObstaclePlatformAnimator *animator =
		 DYNCAST(ObstaclePlatformAnimator*, _animator);
		nf(!animator, "Animator is not ObstaclePlatformAnimator");
		MovingAnimation *animation = animator->getAnimation();
		animation->SetDx(-animation->GetDx());
		animation->SetDy(-animation->GetDy());

		repeats = 0;
	}
}

CPI_DEFINE(custompostinit_start_obstplats) {
	_three<> threes_start[] = {
		  _three<>(true, 1, 6000)
		, _three<>(false, 14, 6001)
		, _three<>(false, 15, 6002)
		, _three<>(true, 25, 6003)
	};
	_three<> *threes_end =
	 threes_start + ( sizeof(threes_start) / sizeof(_three<>) );

	std::for_each(threes_start, threes_end, obstplat_starter(gd, d));
} // custompostinit_start_obstplats

void obstplat_starter::operator() (_three<> &t) {
	ObstaclePlatformAnimator *animator =
	 new ObstaclePlatformAnimator(true);
	animator->SetOnFinish(obstplat_anim_coca, new int(32));
	animator->Start(
	 gd.animdata->plathold->getObstaclePlatform(t.b),
	 gd.animdata->animhold->getMovingAnimation(t.c),
	 d.startingTime);
} // obstplat_starter()

obstplat_starter::obstplat_starter(GameData &_gd, InitData &_d) :
	  gd(_gd)
	, d(_d)
	{ }
