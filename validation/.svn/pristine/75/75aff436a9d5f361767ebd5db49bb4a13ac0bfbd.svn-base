/* Check interprocedural translation of points-to stubs
 *
 * Use an undefined pointer (follow up of inc02, inc03 and inc04).
 */

#include <stdio.h>

void inc06(int *p)
{
  *p = *p + 1;
  return ;
}

int main()
{
  int * p;

  inc06(p);
  
  return *p;
}
