/* Francois Irigoin:
 *
 * Check side effects in struct assignments
 */

typedef struct
{
	int N1;
  	int N2;
} param;

param p[2];
param q;

int struct11()
{
  int i = 0;
  q.N1 = 1;
  q.N2 = 2;

  q = p[i++];

  return 0;
}
