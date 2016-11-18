// similar to for05 but the new bound is made with a die variable :(
// need something like with_live_out_regions (but also live precondition)
// if we pass a dead_code_elimination before LOOP_BOUND_MINIMIZATION_WITH_OUT_REGIONS the problem mustn't occur
//similar to live01 but without the if
#include <stdio.h>

int main()
{
  int a[10], i;
  int l;
  int u;
  
  //al, au are totaly useless for this code but will be revive with LOOP_BOUND_MINIMIZATION_WITH_OUT_REGIONS
  int al, au;
  al=l;
  au=u;
  
  for (i=l; i<u; i++) {
    a[i-l] = i;
  }
  
  for (i=l; i<u; i++) {
    if (i<10)
      a[i] = i;
  }
  
  for (i=0; i<10; i++) {
    printf("a[%d]=%d", i, a[i]);
  }
  
  return 0;
}
