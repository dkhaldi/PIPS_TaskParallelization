# 1 "./linkedlist.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "./linkedlist.c"
# 1 "/usr/include/string.h" 1 3 4

/* retrieved from cpp 5 */

# 3 "./linkedlist.c" 2

  
# 4 "./linkedlist.c"
struct Liste {
  char Chaine[16];

  struct Liste *pSuivant;

};

int main ()
{


  struct Liste *Nouveau;

  struct Liste *Tete;

  Tete = 
# 19 "./linkedlist.c" 3 4
    ((void *)0)
# 19 "./linkedlist.c"
    ;

  // problem of sizeof instrinsic with structure 
  // Nouveau = (struct Liste *)malloc(sizeof(struct Liste));

  Nouveau->pSuivant = Tete;

  Tete = Nouveau;

}
