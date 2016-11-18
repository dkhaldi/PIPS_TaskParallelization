// private/(global) propagation on callgraph

void compute(float * f)
{
  *f = 0.0;
}

void setzero(float * f)
{
  int i;
  for (i = 0; i < 10; i++)
    compute(& f[i]);
}

void stuff00(float * f)
{
  // private array
  float a[10];
  setzero(a);

  int i;
  for (i = 0; i < 10; i++)
    a[i] += f[i];
}

int main(void)
{
  float data[10];
  stuff00(data);
}
