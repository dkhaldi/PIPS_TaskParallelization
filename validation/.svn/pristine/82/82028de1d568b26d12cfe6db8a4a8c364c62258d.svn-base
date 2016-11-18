/* Check handling of memcpy() intrinsics for simple and convex effects.
 *
 * Compare result for intrinsics et for user code
 *
 * Similar to memcpy19.c, but with different pointers.
 */

#include <string.h>

void mymemcpy(char * out, char * in, int l)
{
  int i;
  for(i=0; i<l;i++) {
    out[i] = in[i];
  }
}

int main(int argc, char** argv)
{
  char buffer_in2[10][10];
  char buffer_out2[10][10];
  int n = argc, m = argc, l = argc;

  char (* ip)[10] = &buffer_in2[0];
  char (* op)[10] = &buffer_out2[0];

  // Information on the first dimension lost, l impact the second dimension
  memcpy(op+n, ip+m, l);
  // PIPS does not handle the cast properly
  mymemcpy((char*) op+n, (char*) ip+m, l);

  return 0;
}
