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

  memcpy(&buffer_out2[n][0], &buffer_in2[m][0], l);
  mymemcpy(&buffer_out2[n][0], &buffer_in2[m][0], l);

  return 0;
}
