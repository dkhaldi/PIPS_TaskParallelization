
#include<stdlib.h>
#include <stdio.h>

int main()
{
  int x, y;
  x = 0;
  y = 0;
  if (rand()) {
    printf("x=%d", x);
  }
  else {
    printf("y=%d", y);
  }
  return 0;
}
