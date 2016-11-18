// If run with PIPS r19837, this example requires transformer lists
// to be properly analyzed.

// $Id: transformer_lists_01.c 5188 2011-12-31 09:49:52Z coelho $

#include <stdlib.h>

void error() {
	exit(1);
}

void run() {
	int a;
	int b = 0;
	while (1) {
		a = rand();
		if (rand() % 2) {
			if (rand() % 2 && b != 0) error();
			b = 0;
		}
	}
}

int main(void) {
  run();
  return 0;
}

