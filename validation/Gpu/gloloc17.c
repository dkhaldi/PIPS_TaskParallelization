void setzero(int a[1])
{
  a[0] = 0;
}

void addone(int * a)
{
  *a += 1;
}

void one01(int n, int a[n])
{
  for (int i = 0; i < n; i++)
  {
    setzero(&a[i]);
    addone(a + i);
  }
}

int main(void)
{
  int a[10];
  one00(10, a);
}
