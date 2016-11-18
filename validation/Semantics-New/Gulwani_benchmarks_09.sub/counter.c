// $Id: counter.c 5617 2012-05-02 14:48:53Z maisonneuve $
// http://research.microsoft.com/en-us/um/people/sumitg/benchmarks/pa.html.

#include <stdlib.h>
#define assume(c) {if (!(c)) exit(0);}
#define assert(c) {if (!(c)) exit(1);}

void counter(int x, int n) {
	x = 0;
	assume(x == 0 && n >= 0);
	while (x < n) {
		x++;
	}
	assert(x == n);
}

/* 
 * Predicate set S:
 *     x <= 0, x > 0, x < 0, x >= 0,
 *     n <= 0, n > 0, n < 0, n >= 0,
 *     x - n <= 0, x - n > 0, x - n < 0, x - n >= 0
 */
