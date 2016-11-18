/* Convex array region translation
 *
 * Modified copy of array07.c
 *
 * To check type errors for formal parameter fa wich does not fit the
 * type of actual array a. Apparently, there is a bug in type
 * equality: constant expressions are not evaluated. But, anyway,
 * actual and formal types are deliberately different in this test
 * case.
 */

void update_array(/*short*/ int fa[3][3][3], int fk)
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
  update_array(a, k);
  return 0;
}
