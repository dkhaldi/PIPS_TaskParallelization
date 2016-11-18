// global propagation on callgraph

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

int main(void)
{
  float data[10];
  setzero(data);
}
