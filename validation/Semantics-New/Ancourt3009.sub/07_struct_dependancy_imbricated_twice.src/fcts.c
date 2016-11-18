#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "fcts.h"

void update1( content* a) { 
  #pragma MOTIF
  a->s1.var2 = 8;
  return;
}

void compute1(content* a, int b[100])
{
#pragma MOTIF
  for(int i = 0; i<100; i++) {
    b[i] = a->s1.var2;
  }
  return;
}

void update2( content* a)
{ 
#pragma MOTIF
  a->s2.var2 = 9;
  return;
}

void compute2(content* a, int b[100], int c[100])
{
#pragma MOTIF
  for(int i = 0; i<100; i++) {
    c[i] = b[i] + a->s2.var2;
  }
  return;
}
