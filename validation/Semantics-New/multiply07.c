/* Check side effects impact
 *
 */

#include <stdio.h>

int main()
{
  int i = 2, j = 3, k, l;

  k = i++;

  k = ++i * ++j;

  l = i++ * j++;

  printf("%d\n", k);

  return 0;
}
