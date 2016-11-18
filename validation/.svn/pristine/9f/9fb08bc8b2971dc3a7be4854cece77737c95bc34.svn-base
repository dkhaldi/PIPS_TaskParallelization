/* Check comment placement
 *
 * The comment used to be placed on "if(size==0)".
 */

// #include <stdio.h>

#define FREIA_OK 0
#define FREIA_SIZE_ERROR 1
#define FREIA_INVALID_PARAM 2

typedef int freia_data2d;

typedef int int32_t;
typedef unsigned int uint32_t;

extern int foo(void *);

int if06(int size)
{
  int i, ret;
  /* Main test comment */
  if (foo(((void *) 0))!=1)
    ret = 1;
  else if (size==0)
    ret = 2;

  return ret;
}
