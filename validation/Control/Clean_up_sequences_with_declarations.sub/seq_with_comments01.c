int main()
{
  int i;
  {
    // comment attached to first statement of first inner sequence
    int j=0;
    i = j;
  }
  {
    int k=1;
    i = i + k;
  }
  {
    // comment attached to first statement of third inner sequence
    int l = 2;
    i = i + l;
  }
  return i;
}
