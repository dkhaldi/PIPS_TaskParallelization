/*
 The transformer resulting from the translation of update3 into computeH  is wrong :  T(_s_1[0][var2]) {}
 We expect  predicat : a.s1.var2 == 8, a.s2.var2 == 4 after computeH in the main
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int var2;
} sub;

typedef struct {
	sub s1;
	sub s2;
} content;


void foo(int k)
{
  printf("k= %d\n",k);
}
void update1(content* a) {
  a->s1.var2 = 8;
}

void use1_1(content* a) {
  int k=0;
  printf("val a =%d\n", a->s1.var2);
}

void use1_2(content a) {
  int k=0;
  printf("val a =%d\n", a.s1.var2);
}

void compute1_1(sub s, int b[100]){
  for(int i = 0; i<s.var2; i++) {
    b[i] = s.var2;
  }
}

void compute1_2(sub* s, int b[100]){
   for(int i = 0; i<s->var2; i++) {
    b[i] = s->var2;
  }
}

void update2(content* a) {
  int k=0;
  a->s2.var2 = 7;
}

void compute2_1(sub* s, int b[100], int c[100]){
  int k=0;
  for(int i = 0; i<s->var2; i++) {
    c[i] = b[i] + s->var2;
  }
}

void compute2_2(int* var2, int b[100], int c[100]){
 for(int i = 0; i<100; i++) {
    c[i] = b[i] + *var2;
  }
}

void compute2_3(int var2, int b[100], int c[100]){
  int k=0;
  for(int i = 0; i<100; i++) {
    c[i] = b[i] + var2;
  }
}

void update3(sub *st)
{
  st->var2 = 4;
}

void computeH(sub* s, int b[100], int c[100], int d[100], int e[100]){
  // s->var2 == 7
  int k=0;
  // s->var2 == 7
  update3(s);
   // s->var2 == 4
 compute2_1(s,b,c);
   // s->var2 == 4
  compute2_2(&s->var2,c,d);
   // s->var2 == 4
  compute2_3(s->var2,d,e);
}

int main(int argc, char *argv[])
{
  content a; 
  int b[100];
  int c[100];
  int d[100];
  int e[100];

 update1(&a);
 // a.s1.var2 == 8
 use1_1(&a);

 // a.s1.var2 == 8
 use1_2(a);

 // a.s1.var2 == 8
 compute1_1(a.s1,b);

 // a.s1.var2 == 8
 compute1_2(&a.s1,b);

 // a.s1.var2 == 8
 update2(&a);

 // a.s1.var2 == 8, a.s2.var2 == 7
 computeH(&a.s2,b,c,d,e);

 // a.s1.var2 == 8, a.s2.var2 == 4
 printf("a.s1.var2= %d , a.s2.var2 == %d\n",a.s1.var2, a.s2.var2);
  return 0;
}






