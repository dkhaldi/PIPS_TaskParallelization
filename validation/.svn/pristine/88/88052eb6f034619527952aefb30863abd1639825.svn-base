/* Update of global data structure fields
 *
 * Intraprocedural case, nested structs
 */

struct bar {
  int j;
};

// global structure
struct foo {
  int i;
  struct bar s;
} global_f;

int main(void)
{
  global_f.i = 0;
  global_f.s.j = 2;

  int l = global_f.i + global_f.s.j;

  return 0;
}
