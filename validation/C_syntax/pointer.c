int main()
{
  int *p, x, (*p1)[13], *a[13], **pp, a1[10][20], (**pp1)[10][20], (*a2[10][30])[20];
  int (*q)[10][20], (*(*app[10])[20])[30] ;
  int (*apf[20])(int, int), (*pf)(int);
  x = 5;
  p = &x;
  pp1 = (int (**)[10][20])malloc(200*sizeof(int));
  q = &a1 ;
  pp = (int **)&a1;
  pp = (int **)malloc(200*sizeof(int));
  a[1] = &x;
  p = (int *)malloc(3*sizeof(int));
  p1 = (int  (*)[13])malloc(13*sizeof(int));
  return;
}

