// same as dynamic01, but switch affectation n and declaration a
// with only local variable
// and n is NOT know before the declaration of a that have to be resize
// test with REGIONS_WITH_ARRAY_BOUNDS TRUE(a)/FALSE(b)
// shift of 1 element
// not generate the better solution? switch declaration of a and affectation of n
//   scanf("%d", &n);
//   int a[((1<n && n<=100)?(n-1):99)];
// doable?
#include "stdio.h"

int foo() {
  int n, i;
  int a[100];
  scanf("%d", &n);
  //if (n<=100)
  for(i=1; i<n; i++)
    a[i] = 0;
  return 0;
}
