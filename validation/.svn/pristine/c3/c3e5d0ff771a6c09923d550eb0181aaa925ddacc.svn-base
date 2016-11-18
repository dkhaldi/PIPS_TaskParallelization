/* The effects for the call site of update1 in main are wrong. s2
 * should not appear.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

typedef struct {
	int var2;
} sub;

typedef struct {
	sub *s1;
	sub *s2;
} content;


void update1(content* a) {
  a->s1->var2 = 8;
  return;
}

void use1_1(content* a) {
  printf("val a =%d\n", a->s1->var2);
  return;
}

void use1_2(content a) {
  printf("val a =%d\n", a.s1->var2);
  return;
}

void compute1_1(sub s, int b[100]){
  for(int i = 0; i<100; i++) {
    b[i] = s.var2;
  }
  return;
}

void compute1_2(sub* s, int b[100]){
  for(int i = 0; i<100; i++) {
    b[i] = s->var2;
  }
  return;
}

void update2(content* a) {
  a->s2->var2 = 8;
  return;
}


void compute2_1(sub* s, int b[100], int c[100]){
  for(int i = 0; i<100; i++) {
    c[i] = b[i] + s->var2;
  }
  return;
}

void compute2_2(int* var2, int b[100], int c[100]){
  for(int i = 0; i<100; i++) {
    c[i] = b[i] + *var2;
  }
  return;
}

void compute2_3(int var2, int b[100], int c[100]){
  for(int i = 0; i<100; i++) {
    c[i] = b[i] + var2;
  }
  return;
}
void computeH(sub* s, int b[100], int c[100], int d[100], int e[100]){
  compute2_1(s,b,c);
  compute2_2(&s->var2,c,d);
  compute2_3(s->var2,d,e);
  return;
}

int main(int argc, char *argv[])
{
 // Allocation statique
 sub s1;
 sub s2;
 content a; 

 // pointage sur les adresses statiques
 a.s1 = &s1;
 a.s2 = &s2;

 // Tableaux 
  int b[100];
 int c[100];
 int d[100];
 int e[100];

 // Ecriture => forcement par pointeur
 update1(&a);

 // Lecture par pointeur (USE/DEF_USE ?)
 // use1_1(&a);

 // Lecture par valeur (pour comparer)
 // use1_2(a);

 // Lecture de structure par valeur 
 // compute1_1(*a.s1,b);

 // Lecture de structure par pointeur
 // compute1_2(a.s1,b);

 // update par pointeur
 // update2(&a);

 // Travail au niveau hierarchique (autre box)
 // computeH(a.s2,b,c,d,e);		

  return 0;
}






