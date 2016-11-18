/* Bug provided by Corinne Ancourt
 *
 * Why do we end up with an *ANYMODULE*:*ANYWHERE* ?
*/

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

typedef struct {

  float   x;
  float   y;
} float2;

float2 C[19];

void TEST(int a, float2 tab[a], char* fileName)
{
  FILE *fichier, *fichierOut;
  int i = 0;
  char* filename = "toto.txt";
  fichier = fopen(filename, "r");
  fichierOut = fopen(fileName, "w");

  if (fichier != 0) {
    float val1;
    float2 test;
    for (int i =0; i < a; i++)
      {
	if (fscanf(fichier, "%f ", &val1) != EOF)
	  {
	    test = tab[i];
	    if (test.x > 0.) {
		printf("### Test failed - %s : error l%d\n", filename, i);
		return;
	      }	     
	  }
      }
    fclose(fichier);
    fprintf(fichierOut,"OK");
    fclose(fichierOut);
  }
  else
    printf("--- Test impossible - %s\n", filename);
}

void MT(int n, float2 V[n])
{
  for (int i = 0; i < n; i++){
    V[i].x = 0;
    V[i].y = 1;
  }
}

void main()
{
  int i, j;

  MT(10, C);
  TEST(10, C, "test.txt");

}

