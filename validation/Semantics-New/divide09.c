/* Check analysis of division
 *
 * Example from Syntax/four1.f
 */

#include "stdlib.h"
#include "assert.h"
#include "stdio.h"

int divide09(int n)
{
  int nn = n+n;
  int m = nn/2;
  return m;
}
