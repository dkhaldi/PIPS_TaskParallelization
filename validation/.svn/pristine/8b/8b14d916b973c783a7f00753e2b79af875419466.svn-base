/* Reproduction of a bug seen in bzlib01.c */

int main()
{
  int i;

  while(1)
    /* Comment for the test */
    if(i>0)
      goto lab;
    else
      return i;
 lab:
  return 0;
}
