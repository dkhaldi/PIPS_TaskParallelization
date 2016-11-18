/* Update of global data structure fields
 *
 * Interprocedural case
 *
 * Subset of struct02.c: check that summary transformer for
 * updateFoo() is properly built.
 */

// global structure
struct foo {
  int i;
  int j;
} global_f;

void updateFoo(int i, int j)
{
  global_f.i = i;
  global_f.j = j;
  return;
}
