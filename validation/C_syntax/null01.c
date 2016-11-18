/* test case suggested by Fabien to understand issues with cpp 5
 *
 * Simplified version to explore a bug linked to the analysis of (void *)
 */

int main ()
{
  void * p;

  p = ((void *) 0);
}
