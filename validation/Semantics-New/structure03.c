/* exploit side effects in subscript expressions
 *
 * Without points-to analysis, without proper initialization of p,
 * without using type separation, the information about i is lost
 * before return.
 *
 * Same as structure02, but with ALIASING_ACROSS_TYPES set to FALSE in
 * the tpips file.
 */

typedef struct {
  float re[10];
  float im;
} Cplfloat;

void structure03()
{
  Cplfloat c, * p = &c;
  int  i = 0;

  c.re[i++] = 0.;
  p->re[i++] = 0.;
  return;
}
