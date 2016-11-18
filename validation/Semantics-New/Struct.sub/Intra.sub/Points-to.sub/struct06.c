/* Corinne Ancourt:
 *
 * Bug: The semantics pointer analysis includes struct field analysis
 * when the property SEMANTICS_ANALYZE_CONSTANT_PATHS is added to pass
 * TRANSFORMERS_INTERN_FULL_WITH_POINTS_TO.
 *
 * Modified version of struct04.c using stdin instead of pointer file
 * for IOs. Analyzed with SEMANTICS_ANALYZE_CONSTANT_PATHS but without
 * a pointer analysis.
 */

#include "stdio.h"
#include "assert.h"

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

  int r = fscanf(stdin, "%d", &p.N1);

  p.N1=1;
  if (r == EOF)
    return -1;
  assert(p.N1 <= 256);
  p.N2=6;
  r = fscanf(stdin, "%d", &p.N2);
  if (r == EOF)
    return -1;
  assert(p.N2 <= 193);

  return 0;
}
