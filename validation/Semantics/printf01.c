/* Make sure that effects_to_transformer() ignore so-called package
 * effects, effects on variables of the C library such as IO effects
 * or effects on the random generator seed.
 *
 */

#include <stdio.h>

void printf01()
{
  int i = 1;
  // Here, the transformer should not impact i
  printf("i=%d\n", i);
  // Here, i==1
  return;
}
