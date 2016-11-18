// global/private propagation with a pointer

void pointer00(float * f)
{
  *f = 1.0;

  // empty calls
  f + 1;
  f - 11;
  f;
  f[1];
  & f[2];

  float * g0;
  g0 = f;

  float * h0;
  h0 = f + 2;

  float * k0;
  k0 = & f[3];

  // private
  float data[3] = { 0.0, 1.0, 2.0 };
  float * l0;
  l0 = & data[0];

  float * m0;
  m0 = data + 1;

  float n0;
  n0 = f[0];

  // direct
  float * g1 = f;
  float * h1 = f + 4;
  float * k1 = & f[5];
  float * p1 = (f + 6) - 1;
  float * q1 = f - 3;
}

int main(void)
{
  float data[10];
  pointer00(data);
}
