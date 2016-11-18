/* test case suggested by Fabien to understand issues with cpp 5 */

//#include <string.h>
//#include <stdlib.h>

#define NULL ((void *) 0)

struct Liste {
  char Chaine[16];

  struct Liste *pSuivant;

  };

int main ()
{


  struct Liste *Nouveau;

  struct Liste *Tete;

  Tete = NULL;

  // problem of sizeof instrinsic with structure 
  // Nouveau = (struct Liste *)malloc(sizeof(struct Liste));

  Nouveau->pSuivant = Tete;

  Tete = Nouveau;

}
