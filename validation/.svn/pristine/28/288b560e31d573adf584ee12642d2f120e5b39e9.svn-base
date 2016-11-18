/* Bug detected by Corinne: attempt at dereferencing pointers when no
 * points-to information is available.
 *
 *
 * Same code and tpips script as pointer01, but ALIASING_ACROSS_TYPE
 * is set to true instead of false.
 *
 * It does not matter because the non-constant effect of update() is
 * precise. The caller knows that b is the only variable written by
 * function update().
 */

#include <stdio.h>

int a = 0;
unsigned int b = 0;


void update(int fa, unsigned int * pb)
{
  // "fa" is impacted by dereferenceing "*pb"
  if (fa < 0)
    *pb = 128;
  else
    *pb = 256;
  // Here, the value of "fa" is unknown
  return;
}

int main()
{ 
  int i = 1;
  unsigned int j = 2;
  update(a, &b);
  return 0*(i+j);
}
