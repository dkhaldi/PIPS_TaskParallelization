/* check pragma line number... */
#include <stdio.h>

int test(void)
{
  printf("on line 6\n");
#pragma FOO
  printf("FOO: on line 8\n");
  return 0;
}

int main(void)
{
  printf("on line 14\n");
#pragma \
  BLA
  printf("BLA: on line 17\n");
  return 0;
}
