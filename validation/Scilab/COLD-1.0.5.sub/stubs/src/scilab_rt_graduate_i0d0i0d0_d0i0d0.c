
#include <stdio.h>

#include <stdlib.h>

void scilab_rt_graduate_i0d0i0d0_d0i0d0(int scalarin0, 
    double scalarin1, 
    int scalarin2, 
    double scalarin3,
     double* scalarout0, 
    int* scalarout1, 
    double* scalarout2)
{
  printf("%d", scalarin0);

  printf("%f", scalarin1);

  printf("%d", scalarin2);

  printf("%f", scalarin3);

  *scalarout0 = rand();

  *scalarout1 = rand();

  *scalarout2 = rand();

}
