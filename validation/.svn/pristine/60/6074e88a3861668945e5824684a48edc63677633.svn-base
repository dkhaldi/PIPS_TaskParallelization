#include <stdio.h>

// this declaration is needed by clang C syntax check,
// otherwise it fails because the implicit declaration
// does not match the actual function.
extern void modulo06(unsigned int n, int i, unsigned int a[n]);

int main() {
  int n=10;
  int a[n];
  modulo06(n,0,a);
}


void modulo06(unsigned int n, int i, unsigned int a[n]) {
  i = n%4;
  int j = n%4;
  
  // Here i and j in the precondition should be the same
  printf("%d",a[i]);
}

