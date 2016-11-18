/* Check impact of variable incrementation with wrap-around
 * (i.e. integer overflows). Example given in pipsmake-rc.tex/
 *
 * Same as unsigned12.c, but analyzed with different properties.
 *
 * The transformers are not computed using type information, unlike
 * unsigned 12, but the result seems OK because preconditions are
 * correct before the test condition is evaluated with them.
 *
 * Also, the end has been changed to simplify a bit the hand analysis
 * of the invariants.
 */

#include <stdio.h>

int foo(unsigned char i, unsigned char j)
{
  int k = 0;
  if(i<j) {
    i++, j++;
    if(i<j)
      // true branch, reached most of the time
      // i <= 254, j<= 255
      k = 1;
    else
      // false branch reachable because j may have overflowed from 255 to 0
      // j == 0 (found with PIPS precondition only when i == 255)
      k = 2;
  }
  if(k==0) {
    // i>=j
    scanf("%d", &k);
    k = 0;
  }
  else if(k==1) {
    // i <= 254
    scanf("%d", &k);
    scanf("%d", &j);
    k = 1;
  }
  else if(k==2) {
    // j == 0
    scanf("%d", &k);
    scanf("%d", &i);
    k = 2;
  }
  return k;
}

/* The main below is useful to obtain a precondition with formal
 * parameters in its basis. With a default identity transformer, the
 * value basis is empty and no type information is added.
 *
 * x and y are left uninitialized on purpose.
 */
int main()
{
  unsigned char x, y;
  return foo(x, y);
}
