/* Check handling of memcpy() intrinsics for simple and convex effects.
 *
 * Compare result for intrinsics et for user code
 *
 * 2nd excerpt from memcpy03.c
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

  memcpy(&buffer_out[0], &buffer_in[0], 4);
  mymemcpy(&buffer_out[0], &buffer_in[0], 4);

  return 0;
}
