/* Check handling of memcpy() intrinsics for simple and convex effects.
 *
 * Analyzed with non-constant effects
 */

#include <string.h>

int main(int argc, char** argv)
{
  char buffer_in[100];
  char buffer_out[100];
  char buffer_in2[10][10];
  char buffer_out2[10][10];
  int n = argc, m = argc, l = argc;

  /* 1D buffers */

  memcpy(buffer_out, buffer_in, 4);
  memcpy(&buffer_out[0], &buffer_in[0], 4);
  memcpy(&buffer_out[n], &buffer_in[m], l);

  char * ip = &buffer_in[0];
  char * op = &buffer_out[0];

  memcpy(op, ip, l);
  memcpy(&op[n], &ip[m], l);
  memcpy(op+n, ip+m, l);

  /* 2D buffers */

  memcpy(buffer_out2, buffer_in2, 4);
  memcpy(buffer_out2[0], buffer_in2[0], 4);
  memcpy(&buffer_out2[0][0], &buffer_in2[0][0], 4);
  memcpy(&buffer_out2[n][0], &buffer_in2[m][0], l);

  ip = &buffer_in2[0][0];
  op = &buffer_out2[0][0];

  memcpy(op, ip, l);
  memcpy(&op[n], &ip[m], l);
  memcpy(op+n, ip+m, l);

  return 0;
}
