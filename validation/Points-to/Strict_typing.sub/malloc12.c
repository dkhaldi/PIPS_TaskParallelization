/* Check type sensitivity. Extension of malloc03.c
 *
 * FI: I changed the initialization and the type of pt
 *
 * The initialization was wrong: the allocated bucket is not
 * compatible with "pt++" which add 120 to pt (30 four-byte elements).
 *
 * Currently, the bug is not detected...
 */

#include <stdio.h>
#include <malloc.h>

int main(int argc, char *argv[])
{
  int * pi;
  float * px;
  float * pz;
  int (*pt)[30];

  pi = (int *) malloc(sizeof(int));
  px = (float *) malloc(sizeof(float));
  pz = (float *) malloc(sizeof(float));
  pt = (int (*)[30]) malloc(sizeof(*pt));

  printf("%p\n", pt);

  pt++;

  printf("%p\n", pt);

  return 0;
}
