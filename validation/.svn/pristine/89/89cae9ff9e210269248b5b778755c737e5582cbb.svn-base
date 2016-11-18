/* Check that interprcoedural translation is performed correctly
 * are analyzed
 */

#include <stdio.h>

void update(int b[10])
{
  b[0]++;
  b[1]++;
  b[2]++;
  return;
}

int main(int argc, char ** argv)
{
  int a[10][10];

  a[0][0] = 0;
  a[0][1] = 2;
  a[0][2] = 4;

  update(a[0]);

  printf("%d, %d, %d\n", a[0][0], a[0][1], a[0][2]);

  return a[0][2];
}
