#include <stdio.h>


int modulo08(int argc, char **argv) {
  int n=atoi(argv[1]);
  unsigned int j = n%4;
  
  // j is unsigned and thus cannot be < 0
  // This is only found if property SEMANTICS_USE_TYPE_INFORMATION is set
  return j;
}


