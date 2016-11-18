/* Simple assignment with partially known dereferencement */

int foo(void)
{
  int x;
  return x;
}

int main()
{
  int i = 0, j = 1, k = 2;
  int *p;

  if(foo())
    p = &i;
  else
    p = &k;
  
  j = *p;
  
  // Here, 0<=j<=2
  return j;
}
