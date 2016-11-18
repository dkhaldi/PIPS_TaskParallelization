/* Update of global data structure fields
 *
 * Intraprocedural case, nested structs, simplified version of struct13.c
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
  global_f.s.j = 2;

  return 0;
}
