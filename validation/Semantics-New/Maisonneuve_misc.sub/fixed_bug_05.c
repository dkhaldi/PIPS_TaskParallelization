// Segfaults while computing preconditions with PIPS r20506,
// using transformer lists.
//
// The transition transformer was not expected to be empty as here
// because of call to exit()

// $Id: fixed_bug_05.c 5188 2011-12-31 09:49:52Z coelho $

#include <stdlib.h>

void run(void) {
lbl:
	exit(1);
	goto lbl;
}

int main(void) {
	run();
	return 0;
}

