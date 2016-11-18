/* Check handling of scanf() intrinsics for simple and convex effects.
 *
 * Analyzed with constant effects
 */

#include <stdio.h>

int main(int argc, char** argv)
{
  int a1[100];
  int a2[10][10];
  int n = argc;

  /* 1D buffers */

  scanf("%d", a1);
  scanf("%d", &a1[0]);
  scanf("%d", &a1[n]);

  int * p1 = &a1[0];

  scanf("%d", p1);
  scanf("%d", &p1[n]);
  scanf("%d", p1+n);

  /* 2D buffers */

  // scanf("%d", a2); not type compliant
  scanf("%d", a2[0]);
  scanf("%d", &a2[0][0]);
  scanf("%d", &a2[n][0]);
  scanf("%d", &a2[0][n]);

  int * p2 = &a2[0][0];

  scanf("%d", p2);
  scanf("%d", &p2[n]);
  scanf("%d", p2+n);

  return 0;
}
