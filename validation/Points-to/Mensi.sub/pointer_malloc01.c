#include<stdlib.h>
typedef int * pointer;


pointer alloc_pointer(int v)
{
  pointer p = malloc(sizeof(int));
  *p = v;
  return p;
}


int main(void)
{
  pointer p1;
  p1 = alloc_pointer(13);
  return 0;
}
