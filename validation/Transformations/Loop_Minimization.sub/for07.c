//In this example, LOOP_BOUND_MINIMIZATION_WITH_OUT_REGIONS
// reduce second loop to 0<=i<=4
// and reduce first loop to 5<=i<=9
// need to launch LOOP_BOUND_MINIMIZATION_WITH_OUT_REGIONS 2 times
#include <stdio.h>

int main()
{
  int a[10], i;
  int l = 5;
  int u = l+10;
  
  for (i=l; i<u; i++) {
    a[i-l] = i;
  }
  
  for (i=l; i<u; i++) {
    if (i-l<5)
      a[i-l] = i;
  }
  
  for (i=0; i<10; i++) {
    printf("a[%d]=%d", i, a[i]);
  }
  
  return 0;
}
