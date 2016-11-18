//with a more complicate OUT Regions
//same that for20 but without the if
// first for while make new upper bound MIN(n-1, 2*m-2)
#include <stdio.h>

int main()
{
  int n, m;
  int a[n], b[m];
  int i, j, k;
  
  for (i=0; i<n; i++) {
    a[i] = i;
  }
  for (j=0; j<m; j++) {
    b[j] = a[2*j];
  }
  
  for (k=0; k<m; k++) {
    printf("b[%d]=%d", k, b[k]);
  }
  
  return 0;
}
