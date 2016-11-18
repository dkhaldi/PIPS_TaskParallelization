// SEMANTICS_ANALYZE_CONSTANT_PATH at true is not enough accurent to avoid false positive
// need CHECK_INITIALIZE_VLA_WITH_REGIONS to work

int test() {
  int i, n=10;
  int a[n];
  
  for (i=0; i<n; i++) {
    a[i]=1;
  }
  
  int b[n][a[0]];
  
  for (i=0; i<n; i++) {
    b[i][a[0]]=0;
  }
  
  return b[0][0];
}

int main() {
  return test();
}
