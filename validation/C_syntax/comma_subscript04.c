/* Same as comma_subscript02, but with two dimensional array */

int main() {
  int b[10][10];
  int i=0,j=1,k=2,l=3;
  int *(p)[10][10];

  p[i,j][k,l] = 0;

}
