/* Copy of assign02.
 *
 * Use a more detailed script to understand where problems arise.
 *
 * assign02.tpips provides information about proper effects only, in
 * an interprocedural setting where cumulated and summary effects of
 * the callee are used to compute the proper effect of the caller.
 *
 * The script used here provides information about every step.
 */

#include <stdlib.h>

typedef struct {int entier; float reel;} s_t;

s_t make_s(int i, float x)
{
  s_t * p;

  p = (s_t *) malloc(sizeof(s_t));
  p->entier = i;
  p->reel = x;
  return *p;
}

void assign22()
{
  s_t s;
  int j;

  s = make_s(1, 2.);
  s.entier = 4;

  /* invalid lvalue in assignment */
  /* make_s(1, 2.).entier = 4; */

  /* But this is OK in rhs */
  j = make_s(1, 2.).entier;
}
