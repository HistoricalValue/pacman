#include "CustomPostinit_Commons.hpp"
#include "GameStats.hpp"

CPI_DEFINE(custompostinit_stats){
  gd.stats = new GameStats(SurfaceLoader::getInstance());
  gd.stats->InitialDraw(gd.screen);
}
