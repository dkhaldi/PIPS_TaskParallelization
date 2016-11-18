/* Bug detected by Corinne: attempt at dereferencing pointers when no
 * points-to information is available.
 *
 * Same as pointer02.c, but analyzed with CONSTANT_PATH_EFFECTS
 */

int main()
{ 
  int a = 0, b = 0;
  int * p = &b;
  *p = 12;
  return 0;
}
