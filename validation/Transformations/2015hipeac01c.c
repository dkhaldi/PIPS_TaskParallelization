//continuation of 2015hipeac01 but mannually do factorization of a+b
//want to obtain something like:
// d = a + b;
// for(i=0; i<N;i++) c[i] = d * v[i];

#define N 10

int main()
  {
  int v[10], c[10];
  int a, b, i;

  for(i = 0; i <= 9; i += 1) {
    //PIPS generated variable
    register int v_0 = v[i], c_0;
    int x;
    x = a+b;
    c_0 = x*v_0;
    c[i] = c_0;
  }

  return c[0];
}