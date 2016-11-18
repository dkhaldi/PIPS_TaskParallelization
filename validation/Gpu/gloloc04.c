// global/private propagation by transitivity

#define NULL ((void *) 0)

void propagate00(float * f)
{
  float a[10];
  memset(a, 0, 10*sizeof(float));

  float * b, *c;
  float * q, *r;
  q = f;
  b = a;
  r = q;
  c = b;
  float * s = r;
  float * d = c;
  float * t = s;
  float * e = d;

  // private stuff
  float x = a[0] + f[0];
  float * z = & x;

  // private again stuff
  float w;
  float * v;
  w = a[1] + f[2];
  v = & w;

  // not really used
  float * u0 = NULL;
  float * u1;
  u1 = NULL;
}

int main(void)
{
  float data[10];
  propagate00(data);
}
