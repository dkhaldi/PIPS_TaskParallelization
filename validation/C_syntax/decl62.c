/* Bug when an entity, array, is freed during parsing of the compilation unit.
 *
 * The C parser make decisions too early, especially with pointers to
 * functions which are assumed functions at first, and fixed later.
 */

int foo(int, int);
int bar(int, int);

static int (*array[])( int i, int j) = {
  foo,
  bar,
};

static int (*pfoo) (int, int) = foo;

void decl62()
{
}
