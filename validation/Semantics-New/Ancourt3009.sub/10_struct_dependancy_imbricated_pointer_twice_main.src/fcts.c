#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "fcts.h"

void update1(content* a) {
#pragma MOTIF
  // FI->CA: is this a test about error detection ? The proper warning is issued
  // The type cannot be retrieved by analyzing malloc(), but by
  // analyzing the cast
  // a->s1 = (sub*) malloc(4);
  // a->s1 = (sub*) malloc(sizeof(int));
  a->s1 = (sub*) malloc(sizeof(sub));
  a->s1->var2 = 8;
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

void update2(content* a)
{
#pragma MOTIF
  a->s2 = (sub*)malloc(sizeof(sub));
  a->s2->var2 = 8;
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
