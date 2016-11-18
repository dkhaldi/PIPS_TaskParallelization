/* Two issues:
 *
 * - a very bad bug with updateInt()
 *
 * - integer fields not handled with property SEMANTICS_ANALYZE_CONSTANT_PATH
 *
 * Added by Corinne Ancourt et Fabien Coelho
 */

struct foo {
  int i;
  int j;
};

void updateInt(int * pi)
{
  *pi = 19;
  return;
}

void updateFoo(struct foo * pf)
{
  pf->i = 18;
  pf->j = 1;
  return;
}

int main(void)
{
  int k = 17;
  updateInt(&k);
  struct foo f;
  f.i = 0;
  f.j = 2;
  updateFoo(&f);
  int l = k + f.i + f.j;
  return 0;
}
