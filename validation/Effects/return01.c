#include<stdio.h>

int global = 0;

int return01()
{
  return global++;
}

int main()
{
  printf("global=%d\n", global);
  printf("return01=%d\n", return01());
  printf("global=%d\n", global);
  return 0;
}
