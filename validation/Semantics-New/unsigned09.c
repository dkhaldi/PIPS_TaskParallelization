/* Example submitted by mikhail.ramalho@gmail.com
 *
 * The invariant he seeks, sn==2i, is found by the two different
 * versions of PIPS I tried (FI).
 *
 * I add the example to the PIPS validation suite because of its
 * potential wrt handling unsigned variables.
 */

int main() { 
  unsigned int sn = 0;
  unsigned int i = 0;
  unsigned int n;

  while (i < n)
  {
    sn = sn + 2;
    i++;
  }

  return 0;
}
