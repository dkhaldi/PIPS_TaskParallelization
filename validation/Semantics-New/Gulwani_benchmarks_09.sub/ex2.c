// $Id: ex2.c 5617 2012-05-02 14:48:53Z maisonneuve $
// http://research.microsoft.com/en-us/um/people/sumitg/benchmarks/pa.html.

#include <stdlib.h>
#define assume(c) {if (!(c)) exit(0);}
#define assert(c) {if (!(c)) exit(1);}

void ex2(int x, int i) {
	assume(i >= 0);
	if (i < 10)
		x = 1;
	else
		x = 0;

	// a disjunctive invariant is needed at this point.

	if (x==1)
		assert(i >= 0 && i < 10);
}

/*
 * Predicate Set S:
 * 	x <= 0, x >= 0, x <= 1, x >= 1,
 * 	i <= 10, i >= 10, i < 10, i > 10,
 * 	i <= 0, i >= 0, i < 0, i > 0,
 */
