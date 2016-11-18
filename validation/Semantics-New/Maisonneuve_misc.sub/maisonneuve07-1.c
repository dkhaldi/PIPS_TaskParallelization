// This program has an invariant of kind -b<=x<=b which cannot be
// derived directly from T'(dx)

// $Id: maisonneuve07-1.c 5188 2011-12-31 09:49:52Z coelho $

#include <stdlib.h>

void run(void) {
  int x = 0;
  int t = 0;
  int b = 10; // b > 0 should be enough
  while(1) {
    if(rand() % 2 && x >= -b) x--;
    if(rand() % 2 && x<=b) x++;
    t++;
  }
}

int main(void) {
  run();
  return 0;
}

