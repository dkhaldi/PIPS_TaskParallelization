/* Example provided by Corinne Ancourt
 *
 * Same as struct14, except for file management: stdin is used instead of file
 */

#include "stdio.h"
#include "assert.h"
 
typedef struct
{
	int N1;
	int N2;
	int N3;
	int N4;
	int N5;
} param;

extern param p;

int struct15()
{
  /*
  static FILE* file = NULL;
  if (file == NULL)
    file = fopen("vals_init.txt","r");
  */

  int r = fscanf(stdin, "%d", &p.N1);
  if (r == EOF)
    return -1;
  assert(p.N1 <= 256);

  r = fscanf(stdin, "%d", &p.N2);
  if (r == EOF)
    return -1;
  assert(p.N2 <= 193);

  r = fscanf(stdin, "%d", &p.N3);
  if (r == EOF)
    return -1;
  assert(p.N3 <= 32);

  r = fscanf(stdin, "%d", &p.N4);
  if (r == EOF)
    return -1;
  assert(p.N4 <= 8);

  r = fscanf(stdin, "%d", &p.N5);
  if (r == EOF)
    return -1;
  assert(p.N5 <= 64);

  return 0;
}

