/* Check handling of memcpy() intrinsics for simple and convex effects.
 *
 * Compare result for intrinsics et for user code
 *
 * 3rd excerpt from memcpy03.c
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
  char buffer_in[100];
  char buffer_out[100];
  int n = argc, m = argc, l = argc;

  memcpy(&buffer_out[n], &buffer_in[m], l);
  mymemcpy(&buffer_out[n], &buffer_in[m], l);

  return 0;
}
