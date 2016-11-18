/* To check the handling of constant string by points-to, effects and
 * convex array region analyses
 */

char * s = "hello";

void update2(char * p, int n)
{
  int i = 0;
  for(i=0;i<n;i++)
    s[i] = p[i];
  return;
}

int main(int argc, char **argv)
{
  update2("world", 3);

  return 0;
}
