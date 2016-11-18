/* Bug with update analysis: check subscripts */

int main()
{
  int a, tab[10];

  tab[a++]+=tab[a-1];
  return;
}
