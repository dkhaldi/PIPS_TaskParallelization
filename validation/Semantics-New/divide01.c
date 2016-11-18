/* Check analysis of division
 *
 * Two positive intervals
 */

#include "stdlib.h"
#include "assert.h"

int divide01(int v1, int v2)
{
  int v;
  assert(10<=v1 && v1<=100 && 2<=v2 && v2<=3);
  v = v1/v2;
  return v;
}

int main()
{
  int k = divide01(15, 3);
  return k;
}
