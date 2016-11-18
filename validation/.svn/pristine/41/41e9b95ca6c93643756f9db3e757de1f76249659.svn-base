#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "fcts.h"

void update1(sub** s) { 
  #pragma MOTIF
  *s = (sub*)malloc(sizeof(sub));
  (*s)->var2 = 8;
  return;
}

void compute1(sub s, int b[100])
{
#pragma MOTIF
  for(int i = 0; i<100; i++) {
    b[i] = s.var2;
  }
  return;
}

void update2(sub** s)
{ 
  #pragma MOTIF
  *s = (sub*)malloc(sizeof(sub));
  (*s)->var2 = 7;
  return;
}

void compute2(sub* s, int b[100], int c[100])
{
#pragma MOTIF
  for(int i = 0; i<100; i++) {
    c[i] = b[i] + s->var2;
  }
  return;
}
