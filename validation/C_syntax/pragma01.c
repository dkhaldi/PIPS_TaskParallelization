# 1 "pragma01.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 160 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "pragma01.c" 2

void pragma01()
{
  int i;

#pragma omp parallel for
 for(i = 0; i < 10; i++) {
    int j = i + 1;
  }
  /* Some comment */

#pragma omp parallel for
 // And other
  for(i = 0; i < 10; i++) {
    int j = i + 1;
  }
#pragma omp parallel for


 for(i = 0; i < 10; i++) {
    int j = i + 1;
  }
}
