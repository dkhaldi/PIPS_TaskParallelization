/* Check interprocedural translation of points-to stubs
 *
 * Use an "address-of" pointer argument
 */

void inc02(int *p)
{
  *p = *p + 1;
  return ;
}

int main()
{
  int i = 0;
  inc02(&i);
  inc02(&i);
  
  return i;
}
