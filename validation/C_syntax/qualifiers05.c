/* Multiple variables in a const declaration
 *
 * The main source code is illegal, but ths is not detected by
 * PIPS. This could be a new feature of the effect passes.
 */

struct s {int mem;};

/* The const is in fact carried by struct s, not by cs */
struct s const cs = {1}, vs;

int main()
{
  cs.mem = 2;
  vs.mem = 2;
  return 0;
}