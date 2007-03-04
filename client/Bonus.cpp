#include "Bonus.hpp"

using namespace cs454_2006;

void BonusCallback(Sprite *bonus, Sprite *pacman, void *c){
  
  if(bonus->IsVisible()){ if(c){
    bcoca *bcocz = CAST(bcoca*, c);
    bonus->SetVisibility(false);
    bcocz->cc->Cancel(bonus, pacman);
    bcocz->gs->DrunkChocodrink();
  }
  else
    nf(-1, "fail: closure is NULL");
  }
  return;
}
