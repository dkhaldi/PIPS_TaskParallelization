static struct {
  double a[10];
  double b[10];
} foo;

int main(void)
{
  int i;
  for (i=0; i<10; i++)
  {
    foo.a[i] = 0;
    foo.b[i] = 1;
  }
  return 0;
}
