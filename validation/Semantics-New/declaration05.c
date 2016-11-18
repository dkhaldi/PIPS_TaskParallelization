/* Bug: LF not supported in the midst of a function declaration with a
 * dependent type.
 *
 * The key feature is the declaration of foo, its use of var1 and the
 * declaration of another var1 variable.
 */

void foo(int var1, int var2,
         float out[var1]);

unsigned int var1;

int main(int argc, char* argv[])
{
  int a, b;
  unsigned int i = 0,
   j = 0;

  var1 = 8;
  return 0;
}

