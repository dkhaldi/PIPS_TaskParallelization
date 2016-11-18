
int inc01b()
{
  int i = 0;
  int *p;
  
  p=&i;
  (*p)++;
  // Here, i==1
  return i;
}

int main()
{
  return inc01b();
}
