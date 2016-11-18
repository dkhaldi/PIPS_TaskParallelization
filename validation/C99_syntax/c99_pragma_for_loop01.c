// Bug with declaration inside for init in presence of pragma

int main()
{
  int a[5][6];
#pragma omp parallel for
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 6; j++)
      a[i][j] = i*5 + j;
    
  return 0;
}
