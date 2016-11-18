/* An implicit struct declaration disappears (used to disappear)
 *
 * Same as decl68, but with the static keyword.
 *
 * The static keyword is ignored by gcc and PIPS ignores it too
 */

// The static keyword is ignored for derived entities
static struct c;

// The static keyword is retrieved for x
// static struct c {int a;} x;
