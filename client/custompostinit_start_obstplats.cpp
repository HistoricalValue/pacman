#include "CustomPostinit_Commons.hpp"
#include "ObstaclePlatformAnimator.hpp"

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
	ObstaclePlatform *plat = gd.animdata->plathold->
	 getObstaclePlatform(0x1);
	ObstaclePlatformAnimator *animator =
	 new ObstaclePlatformAnimator(true);
	MovingAnimation *animation = gd.animdata->animhold->
	 getMovingAnimation(6000);
	
	animator->SetOnFinish(obstplat_anim_coca, new int(32));
	animator->Start(plat, animation, d.startingTime);
} // custompostinit_start_obstplats

