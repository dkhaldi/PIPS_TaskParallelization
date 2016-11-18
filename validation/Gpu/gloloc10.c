// global/private errors

void err4(float * a)
{
  *a = 1.0;
}

void error04(float a[10])
{
  err4(a);
  float l[10];
  err4(l);
}

// global -> private
void err56(float * a)
{
  *a = 0.0;
}

void error05(float a[10])
{
  err56(a);
}

void error06(float a[10])
{
  float l[10];
  for (int i = 0; i < 10; i++)
    l[i] = a[i];
  err56(l);
}

// private -> global
void err78(float * a)
{
  *a = 0.0;
}

void error07(float a[10])
{
  float l[10];
  for (int i = 0; i < 10; i++)
    l[i] = a[i];
  err78(l);
}

void error08(float a[10])
{
  err78(a);
}

int main(void)
{
  float a[10];
  error04(a);
  error05(a);
  error06(a);
  error07(a);
  error08(a);
  // err4(a);
  // err56(a);
  return 0;
}
