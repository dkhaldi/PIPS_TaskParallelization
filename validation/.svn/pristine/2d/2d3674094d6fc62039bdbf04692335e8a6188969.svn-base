// E.G. Karpenkov, Program anaysis with local policy iteration
// VMCAI 2016, pp. 127-146

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
    x = x_new;
    x_new = unknown();
  }
  return 0;
}
