/* Legal multiple declaration of variable c
 *
 * See Ticket 430
 */

// Commented out for debug
//#include <stdio.h>

extern int c;
int c;
extern int c;
int c;
extern int c;
/* Here, c is initialized */
int c = 1;
extern int c;

int main(void)
{
  //printf("c=%d\n", c);
  return 0;
}
