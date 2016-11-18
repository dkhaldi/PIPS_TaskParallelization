// Segfaults in deprecated versions of PIPS.

// $Id: fixed_bug_01.c 5188 2011-12-31 09:49:52Z coelho $

#include <stdlib.h>

void run(void) {
  int x;
  while (rand() % 2) {
    if (rand() % 2) {
      if (x < 0) {
        x++;
      }
    }
  }
}

int main(void) {
  run();
  return 0;
}

