#include "CustomPostinit_Commons.hpp"
#include "Bonus.hpp"

CPI_DEFINE(custompostinit_bonus) {
  struct bcoca *bcocz = new bcoca;
  bcocz->cc = d.cc;
  bcocz->gs = gd.stats;
}
