/* Bug detected by Corinne: attempt at dereferencing pointers when no
 * points-to information is available.
 *
 * Simpified version of pointer01.c
 */

int main()
{ 
  int a = 0, b = 0;
  int * p = &b;
  *p = 12;
  return 0;
}
