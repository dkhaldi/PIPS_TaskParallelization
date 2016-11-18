/* Check the impact of points-to properties on the management of null
 * pointers and implicit array pointers.
 */

#include <assert.h>
#define __func__ ((const char *) 0)
void properties03(int n, int *p)
{
  int i;
  int *q = p+i;

  assert(p!=0);

  *(p+i) = 19;

  *q = 1;

  return;
}
