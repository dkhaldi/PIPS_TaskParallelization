// similar to dynamic01 but with explicit test n<=100 (size of a)
// with only local variable
// and n is know before the declaration of a that have to be resize
// test with REGIONS_WITH_ARRAY_BOUNDS TRUE(a)/FALSE(b)
// shift of 1 element
// not generate the better solution? 
//   int a[((1<n)?(n-1):99)];
#include "stdio.h"

int foo() {
  int n, i;
  scanf("%d", &n);
  int a[100];
  if (n<=100)
  for(i=1; i<n; i++)
    a[i] = 0;
  return 0;
}
