/* To illustrate the interprocedural issues with free() */

#include <stdlib.h>
#include <stdbool.h>

int conditional_free02(int *p, bool c1, bool c2, bool c3) {
  int *q = p, i = 0;
  if(c1) p = (int *) malloc(sizeof(int));
  if(c2) {
    free(p);
    i++; // FI: to observe the impact of free(p)
  }
  if(c3) p = (int *) malloc(sizeof(int));
  return *q;
}

int main()
{
  int *p = (int *) malloc(sizeof(int));
  (void) conditional_free02(p, false, true, false);
  return 0;
}
