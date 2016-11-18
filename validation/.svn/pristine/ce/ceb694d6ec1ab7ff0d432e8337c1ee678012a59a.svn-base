#include <stdio.h>
#include <string.h>

typedef struct
{
  float re;
  float im;
} float2;

float2 T0[256];

int a = 0;
int b = 0;
int c = 0;

void init(float2 Sig[256], int *a, int *b, int *c)
{
  int n;
  for (n = 0; n < 256; n++)
    {
      Sig[n].re = 0.0f;
      Sig[n].im = 0.0f;
    }
  *a = -3;
  *b = -2;
  *c = -2;
  return;
}

int testResult(int x, float2 tab[x], char * filenameIn, char* fileNameOut, int *a, int *b, int c)
{
  //FILE *fichierIn , *fichierOut;
  char abc[30];
  char destination[40] = "";
  sprintf(abc, "%d%d%d.txt", *a, *b, c);
  strcat(destination, filenameIn);
  //strcat(destination, abc);
  //fichierIn = fopen(destination, "r");
  return 0;
}

int main()
{
  init(T0, &a, &b, &c);
  testResult(256, T0, "m", "test.txt", &a, &b, c);
  return 0;
}
