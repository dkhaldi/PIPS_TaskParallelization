/* How are LFs managed with comments?
 *
 * Trying to reproduce bug seen in enum_typedef, forloop07 and 08,
 * goto, ngspice and pragma09. A LF within comments, between two
 * comments, is ignored because they occur within a statement.
 *
 * The end of line comment ends up attached to the next statement or
 * be forgotten if no next statement exists.
 */


/* A first comment before the statement */
int /* A second comment, within the statement*/ i; // And an end of line comment

int j;
