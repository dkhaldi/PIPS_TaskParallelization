// need SEMANTICS_ANALYZE_CONSTANT_PATH at true to not make false positive
// or CHECK_INITIALIZE_VLA_WITH_REGIONS may also work

int test() {
  int a[1];
  a[0]=1;
  
  int b[a[0]];
  b[0]=0;
  
  return b[0];
}

int main() {
  return test();
}
