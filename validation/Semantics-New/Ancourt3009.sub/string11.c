/* Derived from string09 for intrinsics strncmp() */

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


int string11(int x, float2 tab[x], char * filenameIn, char* fileNameOut, int *a, int *b, int c)
{
  char abc[30];
  char destination[40] = "";
  sprintf(abc, "%d%d%d.txt", *a, *b, c);
  return strncmp(destination, filenameIn, 10);
}
