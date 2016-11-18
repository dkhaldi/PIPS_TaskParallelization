/* we might want p=*HEAP*_...
 * improvement, semantic when we free pp or *pp?? we lost p=*HEAP*_...
 *
 * If heap locations are not atomic, we cannot use them in the
 * semantics analysis, because p==heap ^ q==heap does not imply p==q
 */

#include<stdlib.h>

int main()
{
  int i = 1;
  int * q = &i; // added to observe the impact of abstract locations
  // when abstract effects are used to eliminate some information in
  // transformers at the end of statement_to_transfoermer
  int *p;
  int **pp;
  
  pp = malloc(sizeof(*pp));
  *pp = malloc(sizeof(**pp));
  p = *pp;
  
  free(*pp);
  free(pp);
  
  return 0;
}
