/* Legal double declaration of C
 *
 * Same as double_declaration13.c, but with the extern declaration at the end
 *
 * Bug: the second declaration is changed into "external int c;" and c
 * is not initialized in the third declaration, "int c, d;". The first
 * and fourth declarations are OK.
 *
 * Together with case double_declaration13.c, this seems to show that
 * the last declaration "wins" over the first ones.
 *
 * See Ticket 430
 */

int c, d = 1;
int c;
int c = 1, d;
extern int c;
