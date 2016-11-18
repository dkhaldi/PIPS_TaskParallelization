
#include<stdlib.h>
#include <stdio.h>

int main()
{
  int x, y;
  if (rand()) {
    x = 0;
    printf("x=%d", x);
  }
  else {
    y = 0;
    printf("y=%d", y);
  }
  return 0;
}
