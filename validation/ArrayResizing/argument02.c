// similar to argument01 but with explicit test n<=100 (size of a)
// with argument for loop bound
//
// test with REGIONS_WITH_ARRAY_BOUNDS TRUE(a)/FALSE(b)
// shift of 1 element
// not generate the better solution? 
//   int a[((1<n)?(n-1):99)];


int foo(int n) {
  int i;
  
  int a[100];
  if (n<=100)
  for(i=1; i<n; i++)
    a[i] = 0;
  return 0;
}
