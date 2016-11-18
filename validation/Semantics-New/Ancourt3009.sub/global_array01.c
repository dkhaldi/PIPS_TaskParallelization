/* Global variable passed as actual argument
 *
 */

#include <stdio.h>
#include <string.h>

int A[10];

void Init(int taille, int Out[taille], int val)
{
  int i;
  for ( i =0; i<taille; i++) {
    Out[i] = val;
  }
  return;
}

void Test(int size, int tab[size], int res)
{
  FILE* fichierOut = fopen("test_out.txt", "w");

  int i;
  for ( i =0; i<size; i++) {
    if (tab[i] != res) {
      fprintf(stderr, "erreur lors du test : %d - val : %d\n", i,tab[i]);
      return;
    }
  }
  fprintf(fichierOut, "OK");
  fclose(fichierOut);
  return;
}


int main()
{
  Init(10,A,3);
  Test(10,A, 7);
  return 0;
}
