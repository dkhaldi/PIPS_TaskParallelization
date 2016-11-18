// global structure
static struct foo {
  int i;
  int j;
} global_f;

void updateFoo(int i, int j)
{
  global_f.i = i;
  global_f.j = j;
  return;
}

int main(void)
{
  global_f.i = 0;
  global_f.j = 2;

  updateFoo(21, 29);

  int l = global_f.i + global_f.j;

  return 0;
}
