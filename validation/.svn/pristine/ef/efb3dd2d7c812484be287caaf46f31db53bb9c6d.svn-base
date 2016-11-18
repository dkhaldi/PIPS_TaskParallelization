// trying clone transformations in C with Fortran intrinsics...

#include <stdio.h>

void clonee(int i, int j)
{
  int k;

  if(i==j)
    k = MIN(i,j);
  else
    k = MAX(i,j);
  printf("%d\n", k);
}

int main()
{
  clonee(1,1);
  clonee(2,3);
  clonee(2,2);
  return 0;
}
