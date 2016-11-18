#include<stdlib.h>

int main()
{
  int a[0];
  a[0] = 0;
  
  if (rand()) {
    a[0] = 1;
  }
  else {
    a[0] = 2;
  }
  
  return a[0];
}
