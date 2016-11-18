
#include<stdlib.h>
#include <stdio.h>

int main()
{
  int x, y;
  x = 0;
  y = 0;
  if (rand()) {
    x = 1;
    printf("x=%d", x);
  }
  else {
    y = 1;
    printf("y=%d", y);
  }
  return 0;
}
