
#include "Waypoint.hpp"

int main(int a, char**b) {
	Waypoint* w[] = 
	{ new Waypoint(0, 0, true, true, false, false, 33),
	  new Waypoint(0, 0, Waypoint::UP | Waypoint::DOWN, 33) };
	
	for (int i = 0; i < 2; i ++)
		printf("up(%d) right(%d) down(%d) left(%d)\n",
		 w[i]->canGoUp(), w[i]->canGoRight(), w[i]->canGoDown(),
		 w[i]->canGoLeft());

	return 0;
}
