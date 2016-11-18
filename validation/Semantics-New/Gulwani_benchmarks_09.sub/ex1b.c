// $Id: ex1b.c 5617 2012-05-02 14:48:53Z maisonneuve $
// http://research.microsoft.com/en-us/um/people/sumitg/benchmarks/pa.html.

#include <stdlib.h>
#define assume(c) {if (!(c)) exit(0);}
#define assert(c) {if (!(c)) exit(1);}

void ex1b(int x, int n, int m) {
	assume(n > 0);
	x = 0;
	m = 0;
	while (x < n) {
		if (rand()) 
			m = x;
		x = x + 1;
	}
	assert(m >= 0 && m < n);
}

/*
 * Predicate Set S:
 *	 x <= 0, x > 0, x < 0, x >= 0,
 *	 m <= 0, m > 0, m < 0, m >= 0,
 *	 x - m <= 0, x - m > 0, x - m < 0, x - m >= 0,
 *	 x - n <= 0, x - n > 0, x - n < 0, x - n >= 0,
 *	 n - m <= 0, n - m > 0, n - m < 0, n - m >= 0,
 */
 
