/* Test assignment of a struct by a constant as it is allowed in
 * C11?
 *
 * Not OK with gcc 4.8.4
 */

int main()
{
  struct {int foo; double bar;} s = {2, 6.28}, t;
  t = s;
  s = {1, 3.14};
  return 0;
}
