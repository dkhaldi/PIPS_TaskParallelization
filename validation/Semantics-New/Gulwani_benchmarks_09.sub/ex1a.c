// $Id: ex1a.c 5617 2012-05-02 14:48:53Z maisonneuve $
// http://research.microsoft.com/en-us/um/people/sumitg/benchmarks/pa.html.

#include <stdlib.h>
#define assume(c) {if (!(c)) exit(0);}
#define assert(c) {if (!(c)) exit(1);}

void ex1a(int x, int y) {
	assume(x >= 0 && x <= 2 && y >= 0 && y <= 2);
	while (rand()) {
		x = x + 2;
		y = y + 2;
	}
	if (y == 0 && x <= 4) {
		assert(x < 4);
	}
}

/*
 * Predicate Set S:
 *
 *	x <= 0, x > 0, x < 0, x >= 0,
 * 	y <= 0, y > 0, y < 0, y >= 0, 
 * 	x - y <= 2, x - y > 2, x - y < 2, x - y >= 2
 */
