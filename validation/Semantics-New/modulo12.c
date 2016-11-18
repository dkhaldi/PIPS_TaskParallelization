/* Example to check modulo analysis
 *
 * See Function matrices_to_1D_lattice() in linear/src/matrix/smith.c 
 *
 * Example with redundancy
 */

void modulo12(void)
{
  int i, j, k, mi, mj, mk, l;
  if(2*i+4*j==2 && 4*i+8*j==4 && 2*k==2 && i>=0) {
    // i is odd, mi==1
    mi = i%2;
    // j's parity is not constrained by equation i+2j=1
    mj = j%2;
    // k==1, hence mk==1
    mk = k%2;
    l = 0;
  }
  return ;
}
