//Example to see some limit of regions/transformer/precondition analyzes
// We can detect that we only enter else case of first if
// but not for the second if

int main()
{
  int x, y, n, m, a[10];
  
  a[0] = 0;
  a[1] = 1;
  x = -1;
  n = 3;
  m = 2;
  
  if (n<m) {
    x = a[0];
  }
  else {
    x = a[1];
  }
  // only to know if x is know
  a[2] = x;
  
  if (x == a[0]) {
    y = -1;
  }
  else if (x == a[1]) {
    y = 42;
  }
  
  // only to know if y is know
  a[2] = y;
  
  return y;
}
