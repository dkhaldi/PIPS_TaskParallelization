/* Check analysis of division
 *
 * Two asymetric unsigned intervals
 */

#include "stdlib.h"
#include "assert.h"
#include "stdio.h"

int divide06(int v1, int v2)
//int main()
{
  int v;
  scanf("%d", &v1);
  scanf("%d", &v2);
  assert(-100<=v1 && v1<=200 && -3<=v2 && v2<=2);
  v = v1/v2;
  printf("%d\n", v);
  return v;
}
