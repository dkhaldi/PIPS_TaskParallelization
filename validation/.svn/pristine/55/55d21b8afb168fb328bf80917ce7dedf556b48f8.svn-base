/* Check that interprcoedural translation is performed correctly
 * are analyzed
 */

#include <stdio.h>

void init(int b[10])
{
  b[0] = 0;
  b[1] = 2;
  b[2] = 4;
  return;
}

int main(int argc, char ** argv)
{
  int a[10][10];

  init(a[0]);

  printf("%d, %d, %d\n", a[0][0], a[0][1], a[0][2]);

  return a[0][2];
}
