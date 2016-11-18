/* To check the handling of constant string by points-to, effects and
 * convex array region analyses
 *
 * Bug: interferences dans le calcul de binding entre les deux appels
 * a update2. Probably unwelcome side-effects? In fact, the binding of
 * s is added to the points-to in that reaches the second call site.
 *
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
  char * p1 = "good";
  char * p2;
  p2 = "morning";
  // update2("world", 3);
  update2(p1, 3);
  update2(p2, argc);
  return 0;
}
