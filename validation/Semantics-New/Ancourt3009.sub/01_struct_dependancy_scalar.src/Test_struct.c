#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "fcts.h"

int main(int argc, char *argv[])
{
  content a; 
  int b[100];
  int c[100];

  update1(&a);
  // Here, a.var1==8
  compute1(&a,b);
  update2(&a); 	
  // Here, a.var1==8, a.var2==9
  compute2(&a,b,c);		

  return 0;
}






