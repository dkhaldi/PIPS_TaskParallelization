/* Bug when an entity, array, is freed during parsing of the compilation unit.
 *
 * The C parser make decisions too early, especially with pointers to
 * functions which are assumed functions at first, and fixed later.
 *
 * Simplified version of decl62, to locate a bug
 */

static int (*array[])( int i );
