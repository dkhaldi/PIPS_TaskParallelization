// global/private propagation with scopes

void scope00(float a[10])
{
  float * b = a;
  if (b)
  {
    float * c = b;
    while (c < a + 10)
    {
      *c++ = 0.0;
    }
  }
  else
  {
    for (float * d = b; d < b + 10; d++)
      *d = 1.0;
  }
}

int main(void)
{
  float a[10];
  scope00(a);
  return 0;
}
