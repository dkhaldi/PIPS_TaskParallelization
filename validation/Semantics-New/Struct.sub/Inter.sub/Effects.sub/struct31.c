/* Francois Irigoin:
 *
 * Check struct assignment by an unnown struct.
 *
 * Derived from struct11.c
 */

typedef struct
{
	int N1;
  	int N2;
} param;

param p[2];
param q;

int struct31()
{
  int i = 0;

  q = p[i];

  return 0;
}
