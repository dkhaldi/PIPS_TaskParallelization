/* Variation on pointer01.c, with the formal parameter pb modified
 *
 * Non constant effects are used and, without any pointer analysis,
 * the effect of update() should not be found to be exactly a write on
 * pb[0] in the caller and hence b in the callee.
 *
 */

#include <stdio.h>

int a = 0;
int b = 0;

void update(int fa, int * pb)
{
  int k = 128;
  /* The update of pb should force a conversion of effect pb[0] into
   * an abstract effect.
   *
   * Though the impact of *pb = is not observable from the callee as
   * fa is a copy, the above mentioned conversion will be observable.
   */
  pb = &fa; // 
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
