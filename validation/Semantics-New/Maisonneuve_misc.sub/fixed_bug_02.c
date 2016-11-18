// Segfaults in deprecated versions of PIPS.

// $Id: fixed_bug_02.c 5188 2011-12-31 09:49:52Z coelho $

#include <stdlib.h>

void run(void) {
	int n = 0;
	while (1) {
		if (rand()) {}
	}
}

int main(void) {
	run();
	return 0;
}

