/* Naming of location entities: the constant subscript expressions
 * must be evaluated before a location name is generated.
 *
 * Bug: two different locations are generated for the same element
 *
 * This is due to the effect computation, which does not evaluate the
 * subscript expressions, because they must be preserved to restore
 * the user source code, and which share them using "preference" cells
 * to save some memory space (design of 1988).
 */

int main()
{
  short int a[3][3][6/2];

  a[1][1][4/2] = 0;
  a[1][1][2] = 1;

  return 0;
}
