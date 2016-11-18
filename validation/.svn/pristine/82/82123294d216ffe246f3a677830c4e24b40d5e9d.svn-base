/* Full version of 14_struct.c
 *
 * Bug: effect_backward_translation_error(), call site update_sub in main
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
  float   x;
  float   y;
} float2;

typedef struct {
  int k1;
  int k2;
} sub2;

typedef struct {
  int var2;
  sub2 *var3;
} sub;

typedef struct {
  float2 s1;
  float2 s2[3];
  sub s3;
} content;

void update_float(float *t)
{
  *t=0.0;
  return;
}

void update_float2(float2 *t)
{
  t->x=0.0;
  t->y=0.0;
  return;
}

void update_sub2(sub2 *b)
{
  b->k1=0;
  b->k2=1;
}

void update_sub(sub *s)
{
  s->var2=2;
  update_sub2(s->var3);
  return;
 
}

void update_content(content *a)
{
  int i;

  update_float2(&a->s1);
  //update_float(&a->s1.x);
  for (i = 0; i < 3; i++) 
    update_float2(&a->s2[i]);
  update_sub(&a->s3);
  return;
}


int main()
{
  content ct;
  sub2 s2;
  ct.s3.var3=&s2;
  update_float2(&ct.s1);
  update_float(&ct.s1.x);
  update_float2(&(ct.s2[1]));
  int i;
  for (i = 0; i < 3; i++) 
    update_float2(&ct.s2[i]);
  update_sub(&ct.s3);
  update_content(&ct);
 
  return (0);
}
