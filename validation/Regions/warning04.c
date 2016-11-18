/* Subscript expression for a linearized array
 *
 */

#include "assert.h"

int warning04(int n, int i, double a[n*n])
{
  assert(n>=0 && i>=0);
  a[n*i+i] = 0;
  return i;
}
