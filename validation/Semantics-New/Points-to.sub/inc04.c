/* Check interprocedural translation of points-to stubs
 *
 * Use an address of pointer argument with a struct (follow up of
 * inc02 and inc03).
 */

void inc04(int *p)
{
  *p = *p + 1;
  return ;
}

int main()
{
  struct {int i;} s;
  s.i = 0;
  inc04(&s.i);
  inc04(&s.i);
  
  return s.i;
}
