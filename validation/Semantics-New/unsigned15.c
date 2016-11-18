/* Check impact of variable incrementation with wrap-around
 * (i.e. integer overflows).
 *
 * A precise transformer is needed for i += 3
 */

#include <stdio.h>

int main()
{
  unsigned char i, j;

  i = 254;
  i += 3;
  j = 3*i;
  printf ("j=%d\n", j);

  return j;
}
