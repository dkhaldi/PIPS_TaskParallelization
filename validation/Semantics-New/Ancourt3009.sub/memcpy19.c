/* Check handling of memcpy() intrinsics for simple and convex effects.
 *
 * Compare result for intrinsics et for user code
 *
 * 5th excerpt from memcpy03.c
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

  char * ip = &buffer_in2[0][0];
  char * op = &buffer_out2[0][0];

  // op and ip are char *, l impact the second dimension only
  memcpy(op+n, ip+m, l);
  // op and ip are char *, l impact the second dimension only
  mymemcpy(op+n, ip+m, l);

  return 0;
}
