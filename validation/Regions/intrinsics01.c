// Check handling of MIN and MAX as subscript expression

void foo(int bar[256][256]) {
  int i,j;
  for(i=0;i<256;i++)
    for(j=0;j<256;j++)
      bar[MIN(i,j)][MAX(i,j)]= MIN(i,j);
}
