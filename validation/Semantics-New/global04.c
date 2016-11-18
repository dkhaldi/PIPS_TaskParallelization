// global scalar
int global_i;

void updateInt(int k)
{
  global_i = k;
  return;
}

int main(void)
{
  global_i = 17;
  updateInt(19);
  global_i += 7;
  return 0;
}
