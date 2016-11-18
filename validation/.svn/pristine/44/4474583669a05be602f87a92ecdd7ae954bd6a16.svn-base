/* Side effect in a subscript expression
 *
 */

int warning02(int n, int i, double a[n])
{
  int k = 2;
  /* k is added because sc_add_phi_equation() handles as special cases
   * a[i++] and a[i--], although a more generic approach based on
   * any_expression_to_transformer() is also used for more complex
   * subscript expressions.
   *
   * However, must_p is not computed when
   * any_expression_to_transformer() is used. It would be necessary to
   * check that the phi variable belongs to an equation to preserve
   * must_p.
   */
  a[i++ + k] = 0;
  a[i++ + k] = 0;
  return i;
}
