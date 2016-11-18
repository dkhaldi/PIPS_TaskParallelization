/* FI looking for recursive calls in lhs expressions
 *
 * Shorter version of array09.c
*/

double a[100];

int array18(int *p) {
  a[(*p)+1]= 2.;
  return 0;
}
