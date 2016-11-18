/* Initialization of a pointer with a cast struct expression
 *
 * Excerpt of struct14.c
 *  
 * One LF lost, due to a declaration statement lost by the C parser  
 */

int i;

void *q = (struct s2 {int i; int j;} *) &i;
