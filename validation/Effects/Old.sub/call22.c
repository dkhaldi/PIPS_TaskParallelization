/* To obtain two read effects on a and b and a warning abount
 * ineffective update of i in call02.
 *
 * Copy of call02 to preserve its tpips script.  Hopefully results
 * obtained for call02 will be obtainable again with other semantics
 * option, such as the use of points-to information.
 */

typedef struct two_fields{int one; int two[10];} tf_t;

void call22(int i, int j, int y[10], int * q[10], tf_t *p)
{
  /* i can be modified locally, but it won't show in the summary
     effects... which creates a problem for transformer and
     precondition computation. */
  i = j + 1;
  y[i] = 0;
  p->one = 1;
  p->two[j] = 2.;
  *q[i]=3;
}

main()
{
  int a;
  int b;
  int x[10];
  int * ap[10];
  tf_t s;
  tf_t *sp = &s;

  call22(a, b, x, ap, sp);
}
