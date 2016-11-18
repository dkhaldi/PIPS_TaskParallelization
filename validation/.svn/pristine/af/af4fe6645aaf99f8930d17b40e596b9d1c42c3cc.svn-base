// global/private 2D array

void zero(float * f, float val)
{
  *f = val;
}

void init(float a[10], float val)
{
  int i;
  for (i = 0; i < 10; i++)
    zero(a + i, val);
}

void dims00(float a[10][10], float val)
{
  int i;
  for (i = 0; i < 10; i++)
    init(&a[i], val);
}

int main(void)
{
  float a[10][10];
  dims00(a, 0.0);
}
