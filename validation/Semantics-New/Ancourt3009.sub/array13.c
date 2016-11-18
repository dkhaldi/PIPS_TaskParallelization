/* Array declared as pointed struct field
 */

void update_array(int a[3][3][3], int *pi)
{
  a[0][1][2] = 12;
  (*pi)++;
  return;
}

int main(int argc, char * argv[])
{
  struct {
    int a[3][3][6/2];
  } s, *p;
  int i = 0;
  p = &s;

  update_array(p->a, &i);
  s.a[0][1][2] = 1;

  return 0;
}
