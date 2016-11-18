/* Bug found in gcc source code */

#include <stdio.h>
#include <stddef.h>

extern int __builtin_offsetof();

struct dummy
{
  char c;
  union
  {
    double d;
    int *p;
  } u;
};

int main()
{
  int i =  offsetof (struct dummy, u);
  return i;
}

