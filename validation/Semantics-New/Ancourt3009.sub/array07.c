/* Convex array region translation
 *
 * To explore convex array translation issue in Bug4: not reproduced
 * without separate compilation. The bug occur when a second
 * compilation unit with a declaration of update_array() is
 * parsed. Byt that time, the function decakaration has been analyzed
 * three times: once in the function definition compilation unit, once
 * int the function definition and once in another compilation unit.
 *
 * Another test case should be set up with multiple compilation units,
 * a.k.a. C files.
 */

void update_array(int fk, short int fa[3][3][3])
{
  int i;
  int j;
  for(i=0;i<3;i++)
    for(j=0;j<3;j++)
      fa[i][j][fk] = 0;
}

int main()
{
  short int a[3][3][6/2];
  int k;
  a[1][1][4/2] = 0;
  a[1][1][2] = 1;
  update_array(k, a);
  return 0;
}
