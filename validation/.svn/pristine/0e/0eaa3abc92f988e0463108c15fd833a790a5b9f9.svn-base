// global/private with typedefs

typedef struct { double re, im; } complex;

void typedef01(complex a[10])
{
  complex l[10];
  for (int i = 0; i < 10; i++)
    l[i] = a[i];
  complex * b = a + 3;
  a++;
  complex * c;
  c = & a[0];
  complex *d;
  d = l + 5;
}

int main(void)
{
  complex a[10];
  for (int i = 0; i < 10; i++)
    a[i].re = 1.0, a[i].im = 0.0;
  typedef01(a);
  return 0;
}
