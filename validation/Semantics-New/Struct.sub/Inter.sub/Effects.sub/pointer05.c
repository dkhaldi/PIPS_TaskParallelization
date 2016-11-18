/* Bug detected by Corinne: attempt at dereferencing pointers when no
 * points-to information is available.
 *
 * Same as pointer01.c, but analyzed with CONSTANT_PATH_EFFECTS
 */

#include <stdio.h>

int a = 0;
unsigned int b = 0;


void update(int a, unsigned int* b)
{
  if (a < 0)
    *b = 128;
  else
    *b = 256;
  return;
}

int main()
{ 
  update(a, &b);
  return 0;
}
