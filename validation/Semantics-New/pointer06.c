/* Derived from struct00.c to address the integer pointer issue
 * regardless of the pointed struct issue.
 *
 * Added by Corinne Ancourt et Fabien Coelho
 */

void updateInt(int * pi)
{
  *pi = 19;
  return;
}

int main(void)
{
  int k = 17;
  updateInt(&k);
  return 0;
}
