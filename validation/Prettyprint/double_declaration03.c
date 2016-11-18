/* Legal double declaration of C
 *
 * Same as double_declaration01.c, but declarations have been swapped
 *
 * See Ticket 430
 */

extern int c;
extern int c;

int main(void)
{
  return 0;
}
