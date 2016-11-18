// Check handling of pips_min and pips_max as subscript expression

void foo(int bar[256][256]) {
  int i,j;
  for(i=0;i<256;i++)
    for(j=0;j<256;j++)
      bar[pips_min(2,i,j)][pips_max(2,i,j)]= pips_min(2,i,j);
}
