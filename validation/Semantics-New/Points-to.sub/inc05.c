/* Check interprocedural translation of points-to stubs
 *
 * Use a NULL pointer (follow up of inc02, inc03 and inc04).
 */

#include <stdio.h>

void inc05(int *p)
{
  *p = *p + 1;
  return ;
}

int main()
{
  int * p = NULL;

  inc05(p);
  
  return *p;
}
