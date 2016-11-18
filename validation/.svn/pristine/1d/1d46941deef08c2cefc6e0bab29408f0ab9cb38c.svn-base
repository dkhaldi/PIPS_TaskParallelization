/* call04, excerpt from 15_struct.c
 *
 * Bug: effect_backward_translation_error(), call site update_sub in
 * main, if only because var3 is an undefined pointer...
 *
 */

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


void update_sub2(sub2 *b)
{
  b->k1=0;
  b->k2=1;
  return;
}

void update_sub(sub *s)
{
  s->var2=2;
  update_sub2(s->var3);
  return;
}


int main()
{
  content ct;
  update_sub(&ct.s3);
 
  return 0;
}
