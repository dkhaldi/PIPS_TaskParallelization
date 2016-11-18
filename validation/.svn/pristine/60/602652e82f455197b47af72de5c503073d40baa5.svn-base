/* Check typing error detection (detected in Linear by gcc 5)
 *
 * No warning by PIPS semantics analysis
 */

#include <stdio.h>

int main() {
  int i = 0, j=0;
  int c = -3;

  if(!c>0)
    i = 1;
  else
    i = -1;

  if(!(c>0))
    j = 1;
  else
    j = -1;

  // Expected: i==-1, j==1
  printf("i=%d, j=%d\n", i, j);

  return i;
}
