/* exploit side effects in subscript expressions (copy of structure02)
 *
 * With points-to information, the information about i should be
 * available on return.
 */

typedef struct {
  float re[10];
  float im;
} Cplfloat;

void structure04()
{
  Cplfloat c, * p = &c;
  int  i = 0;

  c.re[i++] = 0.;
  p->re[i++] = 0.;
  return;
}
