#define N 10

static void f(float in[2], float out[2])
{
  out[0] = in[0] + in[1];
  out[1] = in[0] - in[1];
}

void cross00(float a[N], float b[N])
{
  float tmp[2];
  for (int i = 0; i < N/2; i++)
  {
    tmp[0] = a[i], tmp[1] = a[N-i-1];
    f(tmp, &b[2*i]);
  }
}

void zero(float a[N])
{
  for (int i=0; i < N; i++)
    a[i] = 0.0;
}

int main(void)
{
  float a[N], b[N];
  zero(a);
  zero(b);
  cross00(a, b);
}
