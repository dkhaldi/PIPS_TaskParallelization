// David Monniaux, Laure Gonnord: Using Bounded Model Checking to Focus
// Fixpoint Iterations. SAS 2011: 369-385
// Reduced version of listing 2, p. 7.

// $Id: monniaux_sas11_lst2_red.c 5188 2011-12-31 09:49:52Z coelho $

// Transformer lists are required to find the expected invariant (0 <= x <= 99).

#include <stdbool.h>
#include <stdlib.h>

void run(void) {
	int x = 0;
	while (true) {
		if (x < 99 && rand()) x++;
		if (x >= 99 && rand()) x = 0;
	}
}

int main(void) {
	run();
	return 0;
}

