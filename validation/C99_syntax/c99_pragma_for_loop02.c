// Bug with declaration inside for init in presence of pragma
//similar than c99_pragma_for_loop01 but separate pragma into 2 pragma

int main()
{
  int a[5][6];
#pragma omp parallel
#pragma omp for
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 6; j++)
      a[i][j] = i*5 + j;
    
  return 0;
}
