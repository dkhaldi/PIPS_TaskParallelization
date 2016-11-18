/* Bug detected by Corinne: attempt at dereferencing pointers when no
 * points-to information is available.
 *
 * Non constant effects are used and, without any pointer analysis,
 * the effect of update() is found to be exactly a write on pb[0] in the
 * caller and hence b in the callee.
 *
 * Note that ALIASING_ACROSS_TYPES is set to false. Hence the
 * dereferencing of pn in update has not imapact on a or fa because
 * they are int instead of unsigned int.
 */

#include <stdio.h>

int a = 0;
unsigned int b = 0;

void update(int fa, unsigned int * pb)
{
  unsigned int k = 128;
  // "fa" value stays 0 because it is not impacted by the
  // dereferencing "*pb" of an unsigned int
  if (fa < 0)
    *pb = k;
  else
    *pb = 2*k;
  return;
}

int main()
{ 
  int i = 1;
  unsigned int j = 2;
  update(a, &b);
  return 0*(i+(int)j); // to avoid a warning about i and j declarations
}
