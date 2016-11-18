/* call06, half-way fixed version of call04 where the pointer var3 may
 * or not be initialized.
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


void update_sub2(sub2 *pb)
{
  pb->k1 = 0;
  pb->k2 = 1;
  return;
}

void update_sub(sub *ps)
{
  ps->var2 = 2;
  update_sub2(ps->var3);
  return;
}


int main(int argc, char ** argv)
{
  content ct;
  sub2 s2;
  if(argc>2)
    ct.s3.var3 = &s2;
  update_sub(&ct.s3);
 
  return 0;
}
