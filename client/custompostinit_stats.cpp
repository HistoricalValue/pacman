#include "CustomPostinit_Commons.hpp"
#include "GameStats.hpp"

CPI_DEFINE(custompostinit_stats){
  d.stats = new GameStats(SurfaceLoader::getInstance());
  d.stats->InitialDraw(d.screen);
}
