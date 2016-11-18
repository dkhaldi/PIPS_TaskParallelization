/* Check that interprcoedural translation is performed correctly
 * are analyzed
 */

#include <stdio.h>

struct s {int i;};

void init(struct s b[10])
{
  b[0].i = 0;
  b[1].i = 2;
  b[2].i = 4;
  return;
}

int main(int argc, char ** argv)
{
  struct s a[10][10];

  init(a[0]);

  printf("%d, %d, %d\n", a[0][0].i, a[0][1].i, a[0][2].i);

  return a[0][2].i;
}
