/* Check analysis of division
 *
 * Example from Syntax/four1.f
 */

#include "stdlib.h"
#include "assert.h"
#include "stdio.h"

int divide08(int nn)
{
  int m = nn/2;
  assert(nn>=0);
  m = nn/2;
  return m;
}
