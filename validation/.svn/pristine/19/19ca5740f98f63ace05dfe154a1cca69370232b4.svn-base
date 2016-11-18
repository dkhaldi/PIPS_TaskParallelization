// global/private with casts

void casts00(float a[10], float * b)
{
  // globals
  float * p = (float *) a;
  float * q;
  q = (float *) b;
  // privates
  float l[10];
  float * n;
  float * m  = (float *) l;
  n = (float *) m;
  // empty
  (float *) 0;
}

int main(void)
{
  float a[10], b[10];
  casts00(a, (float *) b);
  return 0;
}
