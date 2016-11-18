/* Francois Irigoin:
 *
 * Check struct assignment
 */

typedef struct
{
	int N1;
  	int N2;
} param;

param p;

void foo(int i)
{
  int j = i;
  return;
}

int struct12()
{
  p.N1 = 1;
  p.N2 = 2;

  foo(p.N1);

  foo(p.N2);

  return 0;
}
