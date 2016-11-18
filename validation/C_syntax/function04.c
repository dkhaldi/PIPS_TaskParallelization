/* static qualifier used in an array type and not parsed */

void function04(int size, int a[static size])
{
  int i;
  for(i=0;i<size;i++)
    a[i]=0;
}
