/* This code is not standard conformant because struct s is redeclared
 * in the same scope. gcc detects the error at line 14, conflicting
 * with line 10.
 *
 * This redeclaration is not detected by the PIPS C parser, which
 * detect the issue when filed l is redeclared on line 17.
 */

union
{
  struct s
  {
    int l;
  } d1;
  struct s
  {
    int l;
  } d2;
  int i;
} u;
