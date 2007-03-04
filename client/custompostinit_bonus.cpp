#include "CustomPostinit_Commons.hpp"
#include "Bonus.hpp"

CPI_DEFINE(custompostinit_bonus) {
	struct bcoca *bcocz = new bcoca;
	bcocz->cc = d.cc;
	bcocz->gs = gd.stats;

	// Teh bonus chocodrink
	Sprite *choco = gd.animdata->spritehold->getSprite(7000);

	// Set custom collision callback
	choco->SetCollisionCallback(BonusCallback, bcocz);
	choco->SetVisibility(false);
}
