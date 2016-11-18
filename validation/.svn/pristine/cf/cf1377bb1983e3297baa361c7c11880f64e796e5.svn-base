// E.G. Karpenkov, Program anaysis with local policy iteration
// VMCAI 2016, pp. 127-146

// The while condition is used to replace the assingment to x in the loop

// No information is derived by PIPS although the loop is never
// entered or entered at most once.

#include <stdbool.h>

int unknown(void)
{
  return rand()-rand();
}

int main(void)
{
  int x = 0, x_new = unknown();
  while (2*x_new==x+2)
  {
    x = (x+2)/2;
    x_new = unknown();
  }
  return 0;
}
