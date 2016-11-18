/* Check analysis of division
 *
 * One positive and one negative intervals
 */

#include "stdlib.h"
#include "assert.h"
#include "stdio.h"

int divide03(int v1, int v2)
//int main()
{
  int v;
  scanf("%d", &v1);
  scanf("%d", &v2);
  assert(10<=v1 && v1<=100 && -3<=v2 && v2<=-2);
  // -50 <= v <= -3
  v = v1/v2;
  printf("%d\n", v);
  return v;
}
