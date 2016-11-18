// This program combine three different uses of b: identity, reset
// (involutive) and increment, but in the loop b is always positive

// $Id: maisonneuve08.c 5188 2011-12-31 09:49:52Z coelho $

#include <stdlib.h>

void run(void) {
  int b = 0;
  while(1) {
    if (rand() % 2)
      ;
    else if (rand() % 2)
      b = 0;
    else
      b++;
  }
}

int main(void) {
  run();
  return 0;
}

