/* Derived from line01.c, with extra LF but no # nn lines
 *
 * In this case, the LF have been inserted for some reason by the programmer.
 *
 * Since PIPS strives to respect as much as possible the user layout,
 * the two useless LF below are preserved in PIPS output, however
 * awkwardly as comments.
 *
 * Multiline statements and multiple statements on one line are only
 * given a best effort.
 *
 * Also, line numbers are not provided for declaration of functions
 * and formal parameters, if only because the PIPS internal
 * representation does not provide a field for this piece of
 * information.
 *
 * All in all, how are we supposed to guess that LFs have been
 * inserted by the preprocessor? We should check the line numbers
 * provided by the preprocessor and remove extra LFs that have been
 * stored in the current comment? Not so easy...
 */

# 1 "hello_world.c"
extern fprintf(int, char*);
extern int stdout;
# 3 "hello_world.c"

# 3 "hello_world.c"
int main(void)
{
  fprintf(
         stdout
               , "hello, world!\n");

  fprintf( // on stdout
         stdout // "hello world!"
               , "hello, world!\n");

  fprintf(
	  // on stdout
         stdout
	 // "hello world!"
               , "hello, world!\n");

  int i = 1; int j = 2;
  return i+j;
}
