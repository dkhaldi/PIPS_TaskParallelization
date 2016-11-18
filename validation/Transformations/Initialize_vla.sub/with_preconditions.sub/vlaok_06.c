// need SEMANTICS_ANALYZE_SCALAR_POINTER_VARIABLES at true may work?

int test() {
  int i, n=10;
  int *p;
  p=&n;
  int a[*p];
  
  for (i=0; i<*p; i++) {
    a[i]=0;
  }
  
  return a[0];
}

int main() {
  return test();
}
