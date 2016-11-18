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
  foo(p);
  p = &x;
  foo(p);
  // no information left about x, but information preserved for y and z
  return x+y+z;
}
