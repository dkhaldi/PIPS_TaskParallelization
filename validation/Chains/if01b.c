// use-def chains with if/else
// and declaration with init
// no dependence between if and else case have to be done

#include <stdlib.h>

int if01b()
{
  int r=0;

  if (rand())
    r = 1;
  else
    r = 0;

  return r;
}
