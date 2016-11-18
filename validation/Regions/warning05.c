/* Subscript expression for a linearized array
 *
 * Thanks to a constant, the subscript is affine. No warnings.
 */

#include <stdlib.h>
#include <stdio.h>
#define assert(c) if(!(c)) exit(1)

int warning05(int n, int i, double a[n*n])
{
  assert(n==4);
  a[n*i+i] = a[n*i+i]+1.;
  return i;
}

int main()
{
  int i, n;
  double a[100];
  (void) warning05(n, i, a);
  printf("%g\n", a[i]);
}
