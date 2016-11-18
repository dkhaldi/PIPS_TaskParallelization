//In this example, LOOP_BOUND_MINIMIZATION_WITH_OUT_REGIONS do nothing

int main()
{
  int a[10], i;
  
  for (i=0; i<10; i++) {
    a[i] = i;
  }
  
  return a[0] + a[9];
}
