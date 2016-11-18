/* Parallelizarion with pointers */
#include <stdlib.h>
#include <assert.h>
#undef NULL
#define NULL ((void*)0)
void pointer11(int n, float *p, float *q)
{
  assert(p!=NULL && q!=NULL);

  int i;
  p = q;

  for(i=0; i<n; i++)
    p[i] = q[i];

  return;
}
