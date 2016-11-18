/* Make sure that effects_to_transformer() ignore so-called package
 * effects, effects on variables of the C library such as IO effects
 * or effects on the random generator seed.
 *
 * Same as printf02, but on a non standard file (property
 * USER_EFFECTS_ON_STD_FILES is set to FALSE, the default value).
 *
 * OK, it should be called fprintf01.c to be consistent.
 */

#include <stdio.h>

void printf04(FILE * p)
{
  int i = 1;
  // Here, the transformer should impact i, regardless of the property
  // USER_EFFECTS_ON_STD_FILES
  fprintf(p, "i=%d\n", i);
  // Here, the value of i is unknown
  return;
}
