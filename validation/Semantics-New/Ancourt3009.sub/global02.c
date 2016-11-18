/* Access to a global array of struct, T0, as actual parameter */

#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct
{
  float re;
  float im;
} Cxfloat;


Cxfloat T0[256];
int d = 0;

void init(Cxfloat A[256]) 
{
  for (int n = 0; n < 256; n++) {
    A[n].re=1.0;
    A[n].im=0.0;
  }
  return;
}

void Y(Cxfloat K1[256], int* pk)
{
  int n;
  *pk = 0;
  for (n = 0; n < 256; n++) {
    if (K1[n].re > 0.0)
      (*pk)++;
  }
  return;
}

int main()
{
  init(T0);
  Y(T0,&d);
  return 0;	
}
