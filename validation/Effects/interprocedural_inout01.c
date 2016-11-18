#include <stdio.h>

void init(int a[10]) {
  for (int i=0; i<10; i++) {
    a[i] = i;
  }
}

void update(int a[10]) {
  for (int i=0; i<10; i++) {
    a[i] = i+10;
  }
}

void read(int a[10]) {
  for (int i=0; i<10; i++) {
    printf("%i", a[i]);
  }
}

int main(){
  int a[10];
  init(a);
  update(a);
  read(a);
  return 0;
}