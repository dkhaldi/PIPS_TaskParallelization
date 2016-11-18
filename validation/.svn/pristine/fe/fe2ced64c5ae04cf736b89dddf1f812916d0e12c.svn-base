/* Check update operators for stubs: same as pointer04, but pointers
 * are analyzed.
 *
 * Bug in semantics pointer analysis: value for p!
 */

int main(int argc, char * argv[])
{
  int i = 2;
  int * p = &i;
  (*p)++;
  *p += 3;
  return *p;
}
