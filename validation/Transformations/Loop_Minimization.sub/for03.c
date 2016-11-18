//In this example, LOOP_BOUND_MINIMIZATION_WITH_OUT_REGIONS
// reduce second loop to 0<=i<=4
// and reduce first loop to 5<=i<=9
// need to launch LOOP_BOUND_MINIMIZATION_WITH_OUT_REGIONS 2 times

int main()
{
  int a[10], i;
  
  for (i=0; i<10; i++) {
    a[i] = i;
  }
  
  for (i=0; i<10; i++) {
    if (i<5)
      a[i] = i;
  }
  
  return a[0] + a[9];
}
