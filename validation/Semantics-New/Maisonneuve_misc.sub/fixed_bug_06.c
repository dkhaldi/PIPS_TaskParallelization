// Wrong preconditions found by PIPS r20573 (i == 0 instead of i >= 0),
// using transformer lists.

// $Id: fixed_bug_06.c 5188 2011-12-31 09:49:52Z coelho $

#include <stdlib.h>

void run(void)
{
  int i = 0;
  while (rand()) {
    if (rand()) goto incr;
  incr:
    i++;
  }
  return;
}

int main(void)
{
  run();
  return 0;
}
