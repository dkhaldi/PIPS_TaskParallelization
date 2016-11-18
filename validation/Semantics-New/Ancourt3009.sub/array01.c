/* Check that aliasing is taken into account when array element values
 * are analyzed
 */

int main(int argc, char ** argv)
{
  int a[10];

  a[2] = 2;
  a[argc] = 3;
  return a[2];
}
