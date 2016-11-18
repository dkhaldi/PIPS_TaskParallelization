/* Bug: this generates an internal error instead of a user error
 *
 */

void pointer06(int *k)
{
  k = 0;
  *k++;
  return;
}
