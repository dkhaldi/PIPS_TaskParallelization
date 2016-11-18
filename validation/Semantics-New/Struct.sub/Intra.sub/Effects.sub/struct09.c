/* Francois Irigoin:
 *
 * Check anywhere effect computation when property
 * ALIASING_ACROSS_TYPE is set to false.
 */

#include "stdio.h"

int read_config_file()
{
  FILE* file = NULL;
  int i;

  file = fopen("foo.txt","r");

  fscanf(file, "%d", &i);

  return 0;
}
