#include <stdlib.h>


int main()
{
   // Generated by Pass VARIABLE_REPLICATION
   int __i_0, __i_1, __i_2, __i_3, __j_0, __j_1, __j_2, __j_3;
#pragma distributed on_cluster=0
   {
      __i_0 = 0;
      __i_1 = __i_0;
      __i_2 = __i_0;
      __i_3 = __i_0;
      __j_0 = 0;
      __j_1 = __j_0;
      __j_2 = __j_0;
      __j_3 = __j_0;
   }

#pragma distributed on_cluster=1
   if (rand()) {
      __i_1++;
      __i_0 = __i_1;
      __i_2 = __i_1;
      __i_3 = __i_1;
   }
   else {
      __j_1++;
      __j_0 = __j_1;
      __j_2 = __j_1;
      __j_3 = __j_1;
   }

#pragma distributed on_cluster=2
   if (rand()) {
      __i_2++;
      __i_0 = __i_2;
      __i_1 = __i_2;
      __i_3 = __i_2;
   }
   else {
      __j_2++;
      __j_0 = __j_2;
      __j_1 = __j_2;
      __j_3 = __j_2;
   }

   return 0;
}