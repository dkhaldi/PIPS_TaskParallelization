
#include <stdio.h>

# 4729 "temp.c"
static void print_array(int m, int n, double B[3840+0][3000+0])
{
   int i, j;

   fprintf(stderr, "==BEGIN DUMP_ARRAYS==\n");
   fprintf(stderr, "begin dump: %s", "B");
   for(i = 0; i <= m-1; i += 1)
      for(j = 0; j <= n-1; j += 1) {
         if ((i*m+j)%20==0)
            fprintf(stderr, "\n");
         fprintf(stderr, "%0.2lf ", B[i][j]);
      }
   fprintf(stderr, "\nend   dump: %s\n", "B");
   fprintf(stderr, "==END   DUMP_ARRAYS==\n");
}



int main(int argc, char** argv)
{
  /* Retrieve problem size. */
  int m = 3840;
  int n = 3000;
  
  /* Variable declaration/allocation. */
  double alpha;
  double A[3840+0][3840+0];
  double B[3840+0][3000+0];
  int i, j;

  alpha = 1.5;
  for(i = 0; i <= m-1; i += 1) {
    for(j = 0; j <= i-1; j += 1)
        A[i][j] = (double) ((i+j+1)%m)/m;
    A[i][i] = 1.0;
    for(j = 0; j <= n-1; j += 1)
        B[i][j] = (double) ((n+(i-j))%n)/n;
  }
  
  int i2, j2, k2;
  
  for(i2 = 0; i2 <= 3839; i2 += 1)
    for(j2 = 0; j2 <= 2999; j2 += 1) {
        for(k2 = i2+1; k2 <= 3839; k2 += 1)
          B[i2][j2] += A[k2][i2]*B[k2][j2];
        B[i2][j2] = alpha*B[i2][j2];
    }

  
  print_array(m, n, B);
      
  return 0;
}
