// Check handling of MIN and MAX as pips_min and pips_max
//
// No core dump

void foo(int bar[256][256]) {
    int i,j;
    for(i=0;i<256;i++)
      for(j=0;j<256;j++)
      kernel: bar[MIN(i,j)][MAX(i,j)]= MIN(i,j);
}
