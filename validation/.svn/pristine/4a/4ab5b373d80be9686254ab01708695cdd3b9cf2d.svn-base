/* Legal double declaration of C
 *
 * Same as double_declaration12.c, but with and extern declaration at
 * the beginning.
 *
 * Bug: the extern declaration is changed into "int c;". The extern
 * information is lost.
 *
 * See Ticket 430
 */

extern int c;
int c, d = 1;
int c;
int c = 1, d;
