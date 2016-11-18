/* Check handling of scanf() intrinsics for simple and convex effects.
 *
 * Analyzed with constant effects
 */

#include <stdio.h>

int main(int argc, char** argv)
{
  int a2[10][10];
  int n = argc;

  a2[0][0] = 1;

  scanf("%d", &a2[n][0]);

  return 0;
}
