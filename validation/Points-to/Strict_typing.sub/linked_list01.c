/* How we should compute the fix point for a while loop? */

/* Warning: the formal parameter p is modified within the function
   count() */

#include<stdio.h>
#include<stdlib.h>

typedef struct LinkedList{
  int *val;
  struct LinkedList *next;

}list;

int  count(list *p)
{
  list *q = p;
  int i = 0;
   while( p != NULL){
     p = p->next, i++;
   }

  return i;
}
