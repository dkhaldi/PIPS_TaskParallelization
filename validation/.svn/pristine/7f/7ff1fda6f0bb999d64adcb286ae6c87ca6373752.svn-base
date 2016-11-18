// global/private + kernel

typedef void * kernel;

// also with a static well
void private_zero(float * a)
{
  *a = 0.0;
}

void global_zero(float * a)
{
  *a = 0.0;
}

void stuff(float * a)
{
  float l[10];
  float * p;
  float * q;
  p = a;
  q = l;
  global_zero(p);
  private_zero(q);
}

int main(void)
{
  float a[10];
  stuff(a);
  return 0;
}
