/* A zero-divide used to generate a warning by semantics when it is
 * used by convex effects.
 *
 * Four warnings, at least, are emitted because we have two
 * references, processed by the transformer analysis and then the
 * convex array region analysis.
 */

int warning01(int n, double a[n])
{
  int i = 10, j = 0;

  /* By default, integer divisions are analyzed without exploiting the
   * precondition available when the transformers are computer in
   * context or when they are refined.
   *
   * I suppose, this feature was never needed. And now, a still better
   * analysis is available, up to a property setting. See warning01.tpips.
   */
  a[i/j] = a[i/j] + 1.;
  return i+j;
}
