/* Check impact of variable incrementation with wrap-around
 * (i.e. integer overflows). Example given in pipsmake-rc.tex/
 */

#include <stdio.h>

int main()
{
  unsigned char i, j;

  i = 257;
  j = 3*i;
  printf ("j=%d\n", j);

  return j;
}
