void setzero(float a[1])
{
  a[0] = 0.0;
}

void addone(float * a)
{
  *a += 1.0;
}

void one00(int n, float a[n])
{
  for (int i = 0; i < n; i++)
  {
    setzero(&a[i]);
    addone(a + i);
  }
}

int main(void)
{
  float a[10];
  one00(10, a);
}
