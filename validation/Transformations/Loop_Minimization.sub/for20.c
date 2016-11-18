//with a more complicate OUT Regions
#include <stdio.h>

int main()
{
  int n, m;
  if (n>0 && m>0) {
    int a[n], b[m];
    int i, j, k;
    
    if (n<2*m) {
      for (i=0; i<n; i++) {
        a[i] = i;
      }
      for (j=0; j<m; j++) {
        b[j] = a[2*j];
      }
      
      for (k=0; k<m; k++) {
        printf("b[%d]=%d", k, b[k]);
      }
    }
  }
  return 0;
}
