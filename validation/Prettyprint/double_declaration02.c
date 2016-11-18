/* Legal double declaration of C
 *
 * Same as double_declaration01.c, but declarations have been swapped
 *
 * See Ticket 430
 */

// Commented out for debug
//#include <stdio.h>

int c = 1;
extern int c;

int main(void)
{
  //printf("c=%d\n", c);
  return 0;
}
