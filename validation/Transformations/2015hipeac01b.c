//Same than 2015hipeac01 but without +=
//want to obtain something like:
// d = a + b;
// for(i=0; i<N;i++) c[i] = d * v[i];

#define N 10

int main() {
  int v[N], c[N];
  int a, b, i;
  
  for(i=0; i<N;i++)
    c[i] = a * v[i];

  for(i=0; i<N;i++)
    c[i] = c[i] + b * v[i];

  return c[0];
}