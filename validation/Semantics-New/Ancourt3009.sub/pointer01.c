/* Example in C standard for pointer arithmetic linked to VLAs
 *
 * Section 6.5.6
 *
 * Current state:
 *
 *  - the points-to analysis is correct
 *
 *  - the integer semantics analysis fails to find a[1][2]==99 (fixed)
 *
 *  - the pointer semantics analysis fails to related p and a and hence
 *    does not find the final value of n;
 *
 *  - the region analysis seems OK
 */

int main(int argc, char ** argv)
{
  int n = 4, m = 3;
  int a[n][m];
  int (*p)[m] = a; // p == &a[0]
  p += 1; // p == &a[1]
  (*p)[2] = 99; // a[1][2] == 99
  n = p - a; // n == 1
  return n;
}
