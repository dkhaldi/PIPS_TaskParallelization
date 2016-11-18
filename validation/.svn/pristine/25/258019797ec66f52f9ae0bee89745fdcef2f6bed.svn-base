/* Check handling of scanf() intrinsics for simple and convex effects.
 *
 * Analyzed with constant effects
 */

#include <stdio.h>

int main(int argc, char** argv)
{
  struct {int f;} s;

  scanf("%d", &s.f);

  return 0;
}
