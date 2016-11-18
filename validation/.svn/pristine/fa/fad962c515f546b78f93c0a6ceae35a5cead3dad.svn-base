#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "fcts.h"

void update1( content* a) { 
  #pragma MOTIF
  a->var1 = 8;

  a->tab = (int*)malloc(100*sizeof(int));
  for (int i = 0; i < 100; i++)
  {
	a->tab[i] = i;
  }
  return;
}

void compute1(content* a, int b[100])
{
#pragma MOTIF
  for(int i = 0; i<100; i++) {
    b[i] = a->var1 + a->tab[i];
  }
  return;
}

void update2( content* a)
{ 
#pragma MOTIF
  a->var2 = 9;

  for (int i = 0; i < 100; i++)
    {
      a->tab[i] = 100-i;
    }
  return;
}

void compute2(content* a, int b[100], int c[100])
{
#pragma MOTIF
  for(int i = 0; i<100; i++) {
    c[i] = b[i] + a->var2 + a->tab[i];
  }
  return;
}
