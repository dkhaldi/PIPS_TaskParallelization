/* check the print out of &a[i*k*k] for Benchmark/linpackd.c */
/* Bug in unsplit: the code of void is requested */
/* Bug in prettyprinter or in the prettyprinter: the "extern" keyword was lost */

typedef double REAL;

int foo(int i,int * q)
{
  return i;
}

REAL bar(int i,REAL * r)
{
  return *r;
}

address_of01(int i, REAL * b)
{
  int a[100];
  int j, k;
  int *p;
  REAL * q;
  REAL x;
  extern int foo(int, int *);

  p = &a[i+j*k];
  i = j + foo(i, &a[i+j*k]);
  q = &b[i+j*k];
  x = x + bar(i, &b[i+j*k]);
}
