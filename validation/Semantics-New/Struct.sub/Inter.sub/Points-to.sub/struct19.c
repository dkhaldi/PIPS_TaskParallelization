/* Update of global data structure fields
 *
 * Intraprocedural case, array of struct, expanded from struct18
 */

struct bar {
  int j;
};

// global structure
struct foo {
  int i;
  struct bar s[2];
} global_f[10][10];

int main(void)
{
  global_f[1][1].s[1].j = 2;

  return 0;
}
