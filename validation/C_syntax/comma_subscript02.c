/* Same as comma_subscript01, but with two dimensional array */

int main() {
  int b[10][10];
  int i=0,j=1,k=2,l=3;

  // Unlike Fortran, this is only a one dimensionnal access
  // Pips used to parse it like b[i][j]
  b[i,j][k,l] = 0;

}


