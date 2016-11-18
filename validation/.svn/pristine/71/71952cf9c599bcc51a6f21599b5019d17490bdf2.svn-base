#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
  float   x;
  float   y;
} float2;

 
typedef struct
{
  int N1;
  int N2;
  int N3;
  int N4;
  int N5;
} param;

param p;

void init1(float vals[64])
{
  int j;
  for (j=0; j<=63; j++) 
    vals[j] = 1;

}

void init2(float vals[64], float2 vals_inv[64])
{
  int j = 0;
  for (j = 0; j < 64; j++)
    {
      vals_inv[j].x = vals[j];
      vals_inv[j].y = 0;
    }
}

void foo(int n1, int n2, float in[n1],
	 float2 out[n2][n1])
{
  for (int i = 0; i < n2; i++)
    {
      for (int j = 0; j < n1; j++)
	{
	  out[i][j].x = in[j];
	  out[i][j].y = in[j];
	}
    }
}

int main(int argc, char* argv[])
{
  p.N1 = 256;
  p.N2 = 192;
  p.N3 = 32;
  p.N4 = 8;
  p.N5 = 64;

  float2 in_out[p.N4][p.N3][p.N1];
  float vals_in[p.N5];
  float2 vals_inv[p.N5];
  int i,j;

  init1(vals_in);
  init2(vals_in, vals_inv);
  for (i = 0; i < p.N4; i++)  {
      foo(p.N1, p.N3, vals_in, in_out[i]);
    } 
  return (0);
}

  
