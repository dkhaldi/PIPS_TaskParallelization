/* Case of a 2-D array in a struct 
 *
 * Bug in points-to translation in update_s2 for call to update_sub
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int var2;
} sub;

typedef struct {
  sub s1;
  sub s2[3][2];
  sub s3[4];
} content;


void foo(int k)
{
  printf("k= %d\n",k);
  return;
}

void update_sub(sub *psub1){
  psub1->var2=3;
  return;
}

void update_s2(content* pa) {
  for(int i = 0; i<3;i++) {
    for(int j = 0; j<2; j++) {
      update_sub(&(pa->s2[i][j]));
    }  
  }
  return;
}

void update_s3(content* pa) {
  for(int i = 0; i<4;i++) {
    update_sub(&(pa->s3[i]));
  }
  return;
}

int main(int argc, char *argv[])
{
  // Allocation statique
  content a; 
  int k=0;
  update_s3(&a);
  update_s2(&a);

  for (int i=0; i<a.s2[1][1].var2; i++) foo(k);
  for (int i=0; i<a.s3[2].var2; i++) foo(k);
  return 0;
}






