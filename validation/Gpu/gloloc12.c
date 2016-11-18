// global/private mixed pointers

void mixed00(float a[10])
{
  float l[10];
  // no initializations
  float * b, * m;
  b = a, m = l;
  float * c, * d, * n, * o;
  d = (c = b);
  o = (n = m);
  // with initializations
  float * e = d, * p = o;
  float * f, * q;
  float * g = (f = e), * r = (q = p);
}

int main(void)
{
  float a[10];
  mixed00(a);
  return 0;
}
