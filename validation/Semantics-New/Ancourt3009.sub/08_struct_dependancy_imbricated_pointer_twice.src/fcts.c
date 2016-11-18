#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "fcts.h"

void update1( content* pa) { 
  #pragma MOTIF
  pa->s1 = (sub*)malloc(sizeof(sub));
  pa->s1->var2 = 8;
  return;
}

void compute1(content* pa, int b[100])
{
#pragma MOTIF
  for(int i = 0; i<100; i++) {
    b[i] = pa->s1->var2;
  }
  return;
}

void update2( content* pa)
{ 
#pragma MOTIF
  pa->s2 = (sub*)malloc(sizeof(sub));
  pa->s2->var2 = 8;
  return;
}

void compute2(content* pa, int b[100], int c[100])
{
#pragma MOTIF
  for(int i = 0; i<100; i++) {
    c[i] = b[i] + pa->s2->var2;
  }
  return;
}
