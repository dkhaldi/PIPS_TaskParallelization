/* Bug detected by Corinne: attempt at dereferencing pointers when no
 * points-to information is available.
 *
 * About same as pointer02.c, but analyzed with CONSTANT_PATH_EFFECTS
 *
 * No aliasing across type is selected, hence the values of a and b
 * are not on return, but not the value of c.
 */

int main()
{ 
  int a = 0, b = 0;
  unsigned int c = 2;
  int * p = &b;
  *p = 12;
  return 0;
}
