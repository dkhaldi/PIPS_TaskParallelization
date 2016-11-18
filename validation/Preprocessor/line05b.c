# 1 "line05.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 160 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "line05.c" 2
/* Check line counting with an include file within the function body
 */

int main()
{
  int i = 0;

# 1 "./line05.h" 1
/* To define an array size */


double a[(1024)];
double b[(1024)];
double c[(1024)];
# 8 "line05.c" 2
 return i;
}
