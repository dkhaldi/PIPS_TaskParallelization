/* Update of global data structure fields
 *
 * Intraprocedural case, array of struct
 */

// global structure
struct foo {
  int i;
  int j;
} global_f[10][10];

int main(void)
{
  global_f[1][1].i = 2;

  return 0;
}
