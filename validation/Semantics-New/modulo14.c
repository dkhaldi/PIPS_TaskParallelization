/* Example to check modulo analysis
 *
 * See Function matrices_to_1D_lattice() in linear/src/matrix/smith.c 
 *
 * i = 2 lambda + 4 mu + 1
 * j = 3 lambda + 6 mu + 2
 * k = 3 lambda + 6 mu + 4
 */

void modulo14(void)
{
  int i, j, k, l=1, mi, mj, mk;
  if(3*i-2*j==-1 && l==1 && k==j+2 && l==1 && 3*i-2*k==-5) {
    if(l==1 && i>=0 && j>=0 && k>=0) {
      mi = i%2;
      mj = j%3;
      mk = k%3;
      l = 1;
    }
  }
  return;
}