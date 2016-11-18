/* Copy of pointer01, analyzed with a different script 
 *
 * CONSTANT_PATH_EFFECTS is set to true.
 *
 * ALIASING_ACROSS_TYPES is set to true.
 *
 * EFFECTS_IGNORE_DEREFERENCING is set to TRUE to obtain information
 * about variables that are not updated via a pointer, that is, all
 * variables but b.
 */

#include <stdio.h>

int a = 0;
unsigned int b = 0;

void update(int fa, unsigned int * pb)
{
  unsigned int k = 128;
  // "fa" value stays 0 because it is not impacted by the
  // dereferencing "*pb"
  if (fa < 0)
    *pb = k;
  else
    *pb = 2*k;
  return;
}

int main()
{ 
  int i = 1;
  unsigned int j = 2;
  update(a, &b);
  return 0*(i+(int)j); // to avoid a warning about i and j declarations
}
