/* Interprocedurally conflicting typedefs */

//#include <stdio.h>

typedef int km;

extern km x;

km y = 1;

int main()
{
  extern void foo(km *);
  x = x/2;
  x = x + y;
  //printf("%d %d\n", x, y);
  foo(&x);
  return x;
}
