/* Update of global data structure fields
 *
 * Intraprocedural case
 */

// global structure
struct foo {
  int i;
  int j;
} global_f;

int main(void)
{
  global_f.i = 0;
  global_f.j = 2;

  int l = global_f.i + global_f.j;

  return 0;
}
