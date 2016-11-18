/* Check analysis of division
 *
 * One negative and one positive intervals
 */

#include "stdlib.h"
#include "assert.h"
#include "stdio.h"

int divide02(int v1, int v2)
//int main()
{
  //int v1, v2;
  int v, vm;
  //scanf("%d", &v1);
  //scanf("%d", &v2);
  assert(-100<=v1 && v1<=-10 && 2<=v2 && v2<=3);
  v = v1/v2;
  // vm = v1 % v2;
  // To force an evaluation of v
  //scanf("%d", &v1);
  //gscanf("%d", &v2);
  printf("v=%d, vm=%d\n", v, vm);
  return v;
}

int main()
{
  int k = divide02(-15, 2);
  return k;
}
