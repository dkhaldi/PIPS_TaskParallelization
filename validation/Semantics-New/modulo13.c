/* Example to check modulo analysis
 *
 * See Function matrices_to_1D_lattice() in linear/src/matrix/smith.c 
 *
 * i = 4 lambda + 3
 * j = 5 lambda + 4
 */

void modulo13(void)
{
  int i, j, k, mi, mj;
  if(5*i-4*j==-1) {
    if(i>=0&&j>=0) {
      mi = i%4;
      mj = j%5;
      k = 0;
    }
    else if(i>=0&&j<0) {
      mi = i%4;
      mj = j%5;
      k = 0;
    }
    else if(i<0&&j>=0) {
      mi = i%4;
      mj = j%5;
      k = 0;
    }
    else /* i<0&&j<0 */ {
      mi = i%4;
      mj = j%5;
      k = 0;
    }
    k = 0;
  }
  return;
}
