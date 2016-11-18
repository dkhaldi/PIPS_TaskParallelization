/* Repeated "const" qualifier used in a type and badly prettyprinted
 * (see also function03.c).
 *
 * "const" repeated accepted by gcc 4.6.3
 *
 * The repetition was not detected by PIPS.
 */

void function05(int size, int a[const const size])
{
  int i;
  for(i=0;i<size;i++)
    a[i]=0;
}
