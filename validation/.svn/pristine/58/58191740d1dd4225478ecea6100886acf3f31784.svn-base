/* Example to check modulo analysis
 *
 * See Function matrices_to_1D_lattice() in linear/src/matrix/smith.c 
 *
 * i = 3 lambda + 1
 * j = lambda
 *
 * Check negative values
 */

#include <stdio.h>

int main()
{
  int i, j, mi;

  scanf("%d %d", &i, &j);
  printf("i=%d, j=%d\n", i, j);
  if(i==3*j+1) {
    if(i>=0) {
      mi = i%3;
      printf("mi=%d\n", mi);
    }
    else {
      mi = i%3;
      printf("mi=%d\n", mi);
    }
  }
  else {
    printf("Out of lattice!\n");
  }
  return 0;
}
