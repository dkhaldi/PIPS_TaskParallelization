/* A warning should be generated, no more than if statement k=0; were
 * removed.
 *
 * Derived from pointer06
 */

void pointer07(int *k, int i)
{
  if(i>0)
    k = 0;
  i++;
  *k++;
  return;
}
