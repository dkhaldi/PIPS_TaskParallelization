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
  struct s {
    int a[3][3][6/2];
  } s1, s2, *p;
  int i = 2;

  if(argc>2)
    p = &s1;
  else
    p = &s2;

  update_array(p->a, &i);
  s1.a[0][1][2] = 1;

  return 0;
}
