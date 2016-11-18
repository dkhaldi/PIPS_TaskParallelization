#include<stdlib.h>

int main()
{
  int x;
  x = 0;
  
  if (rand()) {
    x = 1;
  }
  else {
    x = 2;
  }
  
  return x;
}
