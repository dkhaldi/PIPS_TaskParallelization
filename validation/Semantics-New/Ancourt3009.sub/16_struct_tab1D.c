/* 1D array "s3" in structs of type "content"
 *
 * Results are wrong, but no core dump.
 *
 * Spurious messages:
 *
 * Removed location: "main:0`a[s3][2][var2]"
 * Removed location: "main:0`a[s3][0][var2]"
 * Removed location: "main:0`a[s1][var2]"
 *
 * Values projected because of translation error:
 *
 * Value "update_sub:_sub1_1[0][var2]" is projected. Call from "update_s3":
 *
 * 	update_sub(&(a->s3)[i]);
 *
 * Value "update_s3:_a_1[0][s3][0][var2]" is projected. Call from "main"
 *
 *	update_s3(&a);
 *
 * Bugs: 
 *
 * - summary transformer for update_s3 is wrong because the write on a->s3 is lost
 *
 * - transformer in loop for calls to update_sub,
 *   update_sub(&(a->s3)[i]), is wrong; _a_1[0][s3][0][var2] is stated
 *   modified, but it should be _a_1[0][s3][2][var2]
 *
 * Excerpt from this code will be moved into call02.c
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

void update_sub(sub *sub1){
  sub1->var2=3;
  return;
}

void update_s3(content* a) {
  for(int i = 0; i<4;i++) {
    update_sub(&(a->s3[i]));
  }
  update_sub(&(a->s3[2]));
  return;
}

int main(int argc, char *argv[])
{
  content a; 
  int k = 0;
  update_s3(&a);

  for (int i=0; i<a.s3[2].var2; i++)
    foo(k);

  return 0;
}






