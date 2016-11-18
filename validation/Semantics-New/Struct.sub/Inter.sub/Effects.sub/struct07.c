/* Francois Irigoin:
 *
 * Modified version of struct06.c to check the mode behavior of
 * fscanf. Analyzed with SEMANTICS_ANALYZE_CONSTANT_PATHS but without
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
  p.N1=1;

  int r = fscanf(stdin, "%d", &p.N1);

  return 0;
}
