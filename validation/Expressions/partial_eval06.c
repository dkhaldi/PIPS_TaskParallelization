/* Derived from partial_eval04.c to check analysis of static counters
   and global counters and to overcome limits of partial_eval for C
   code: partial_eval assumes side effects on actual parameters */

#include <stdio.h>

int duck_counter = 0;

int duck(int riri[10], int fifi[2][3], int size, int loulou[1][size][6])
{
  static int internal_duck_counter = 0;
  int *zaza = (int *) fifi+(3-1-0+1)*1;
  internal_duck_counter++;
  printf("internal duck counter=%d\n", internal_duck_counter+1);
  duck_counter++;
  return *((int *) riri+2) = *(zaza+1)+*((int *) loulou+3+(6-1-0+1)*(0+(size-1-0+1)*0));
}

int main()
{
  int riri[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int fifi[2][3] = {{10, 11, 12}, {13, 14, 15}};
  int size = 2;
  int loulou[1][size][6];
  int i;
  int j;
  int k = 16;
  int t;
  for (i = 0;i<size;i++)
    for (j = 0;j<6;j++)
      loulou[0][i][j] = k++;
  t = duck(riri, fifi, size, loulou);
  printf("global duck counter=%d\n", duck_counter+1);
  printf("%d\n", t);
  return 0;
}
