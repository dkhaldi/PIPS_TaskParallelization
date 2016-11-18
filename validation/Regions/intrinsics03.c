// Check handling of multiplication as subscript expression

void foo(int bar[256][256]) {
  int i,j;
  for(i=0;i<16;i++)
    for(j=0;j<16;j++)
      bar[i*j][i*j] = i*j;
}
