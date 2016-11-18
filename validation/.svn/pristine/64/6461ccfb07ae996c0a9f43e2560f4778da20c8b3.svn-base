/* Make sure that effects_to_transformer() ignore so-called package
 * effects, effects on variables of the C library such as IO effects
 * or effects on the random generator seed.
 *
 * Same as printf02, but property USER_EFFECTS_ON_STD_FILES is set to TRUE
 *
 * OK, it should be called fprintf01.c to be consistent.
 */

#include <stdio.h>

void printf03()
{
  int i = 1;
  // Here, the transformer should impact i
  fprintf(stdout, "i=%d\n", i);
  // Here, i is unknown
  return;
}
