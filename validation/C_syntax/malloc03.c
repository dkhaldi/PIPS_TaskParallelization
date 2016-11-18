/* Check memory allocation for global variables declared in
 * compilation unit via malloc.h.
 *
 * A recent change seems to have removed the address calculation. In
 * fact, global variable declared external are not allocated.
 *
 * We should check what happens when different files allocate global
 * variables.
 */

#include <malloc.h>

int i = 0;
double a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int k = 0;

int main(int argc, char *argv[])
{
  int * pi;
  float * px;
  char * pc = argv[0];

  pi = (int *) malloc(sizeof(int));
  px = (float *) malloc(sizeof(float));

  return (int) *pc;
}
