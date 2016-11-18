// global/private errors

void error00(float a[10])
{
  float l[10];
  float * p = l;
  p = a;
}

void error01(float a[10])
{
  float l[10];
  float * p = a;
  p = l;
}

void error02(float a[10])
{
  float l[10];
  float * p;
  p = a;
  p = l;
}

void error03(float a[10])
{
  float l[10];
  float * p;
  p = l;
  p = a;
}

int main(void)
{
  float a[10];
  error00(a);
  error01(a);
  error02(a);
  error03(a);
  return 0;
}
