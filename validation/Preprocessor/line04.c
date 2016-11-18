# 1 "line04.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "line04.c"
/* Check line counting with an include file within the function body
 */

int main()
{
  int i = 0;
# 1 "line04.h" 1
/* To define an array size */
# 8 "line04.c" 2
  double a[(1024)];
  a[i] = 0;
  return i;
}
