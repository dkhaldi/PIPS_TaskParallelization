/* Test case submitted by Corinne Ancourt, Aug. 2016
 *
 * An unprecise or wrong malloc() leads to an anywhere effect.
 *
 * A proper malloc is properly analyzed
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
	int var2;
} sub;

typedef struct {
	sub *s1;
	sub *s2;
} content;


void update1(content* a);
void update2(content* a);
void compute1(sub s, int b[100]);
void compute2(sub* s, int b[100], int c[100]);

void update1(content* a) {
  //a->s1 = (sub*) malloc(4);
  //a->s1 = (sub*) malloc(sizeof(int));
  a->s1 = (sub*) malloc(sizeof(sub));
  a->s1->var2 = 8;
}

void compute1(sub s, int b[100]) {
  for(int i = 0; i<100; i++) {
    b[i] = s.var2;
  }
}

void update2(content* a) {
  a->s2 = (sub*)malloc(sizeof(sub));
  a->s2->var2 = 8;
}

void compute2(sub* s, int b[100], int c[100]) {
  for(int i = 0; i<100; i++) {
    c[i] = b[i] + s->var2;
  }
}

int main(int argc, char *argv[])
{
 content a; 
 int b[100];
 int c[100];

 update1(&a);
 compute1(*a.s1,b);
 update2(&a);
 compute2(a.s2,b,c);		

  return 0;
}






