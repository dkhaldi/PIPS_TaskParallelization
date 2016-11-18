/* Check the use and translation of anywhere effect
 *
 * Defined for a smaller version of pointer01.tpips, and then
 * pointer02.tpips used for debugging.
 *
 * Same bug in effect translation for "foo(p)" as in pointer02b.c
 *
 * No precise effect information is sought and the final precondition
 * is empty as expected.
 */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int x;
int y;
int z;

void foo(int *p)
{
  assert(p!=0);
  (*p)++;
}

int main()
{
  x = 1, y = 2, z = 3;
  int *p = (int *) malloc(sizeof(int));
  *p = 10;
  foo(p);
  p = &x;
  foo(p);
  // x==2, y==2 and z==2
  printf("x=%d, y=%d, z=%d\n", x, y, z);
  return x+y+z;
}
