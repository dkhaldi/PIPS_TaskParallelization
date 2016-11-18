/* See if information about s.N1 is exploited by other passes
 *
 * Bug reported by Corinne: s.N1 is not substituted 
 */

/* Just to observe the precondition */
void foo()
{
}

void struct29()
{
  struct foo {int N1;} s;
  int i;
  s.N1 = 10;
  double a[s.N1];
  for(i=0; i<s.N1;i++)
    a[i] = 0.;
  foo(s.N1);
  return;
}
