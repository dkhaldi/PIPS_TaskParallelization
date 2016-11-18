/* Check interprocedural translation of points-to stubs
 *
 * Use a pointer as actual argument
 */

void inc03(int *p)
{
  *p = *p + 1;
  return ;
}

int main()
{
  int i = 0;
  int * p = &i;
  inc03(p);
  inc03(p);
  
  return i;
}
