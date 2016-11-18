/* Corinne Ancourt:
 *
 * The semantics pointer analysis includes struct field analysis when
 * the property SEMANTICS_ANALYZE_CONSTANT_PATHS is added to pass
 * TRANSFORMERS_INTERN_FULL_WITH_POINTS_TO.
*/

#include "stdio.h"
#include "assert.h"
#include <stdlib.h>

typedef struct
{
	int N1;
  	int N2;
} param;

param p;

int read_config_file()
{
  FILE* file = NULL;

  if (file == NULL)
    file = fopen("foo.txt","r");

  int r = fscanf(file, "%d", &p.N1);

  p.N1=1;
  if (r == EOF)
    return -1;
  assert(p.N1 <= 256);
  p.N2=6;
  r = fscanf(file, "%d", &p.N2);
  if (r == EOF)
    return -1;
  assert(p.N2 <= 193);

  return 0;
}
