#include<stdlib.h>

void foo(int **tab)
{
  int *p;
  //if (tab != NULL)
  {
    p=*tab;
    p=p;
  }
}

int main()
{
  int i, *p, **pp;
  i=0;
  p=&i;
  pp=&p;
  
  foo(pp);
  return 0;
}
