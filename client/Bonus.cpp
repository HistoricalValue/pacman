#include "Bonus.hpp"
#include "SoundManager.hpp"

using namespace cs454_2006;

void BonusCallback(Sprite *bonus, Sprite *pacman, void *c){
  
  if(bonus->IsVisible()){ if(c){
    SoundManager::Singleton()->PlayEffect(6, BONUS);
    bcoca *bcocz = CAST(bcoca*, c);
    bonus->SetVisibility(false);
    bcocz->cc->Cancel(bonus, pacman);
    bcocz->gs->DrunkChocodrink();
    bcocz->gs->AddScore(500);
  }
  else
    nf(-1, "fail: closure is NULL");
  }
  return;
}
