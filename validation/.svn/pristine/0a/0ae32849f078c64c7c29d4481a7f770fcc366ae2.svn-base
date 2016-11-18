/* Verify that we return j=0... without points-to information
 *
 * This fails because the preconditions are not used to perform
 * dereferencing.
 */


int main()
{
  int i0=0, i1=1, j=-1;
  int *p, *q;
  p=&i0; q=&i1;
  
  j = (1?*p:*q);
  
  // Here, j==0, but this is not found by the current pointer analysis
  // without points-to information
  return j;
}
