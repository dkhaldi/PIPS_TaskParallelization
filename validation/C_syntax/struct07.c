/* This code is not standard conformant because struct s is
 * redeclared in the same scope
 *
 * The prettyprinter does not reproduce the second declaration of s
 * within the declaration of u.
 */

struct s
{
  int l;
} d1;

union
{
  struct s
  {
    int l;
  } d;
  int i;
} u;
