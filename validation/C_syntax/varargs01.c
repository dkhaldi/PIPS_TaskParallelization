#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

int varargs01(FILE * stream,const char * fmt,...)
{
  if(stream)
    {
      va_list pa;
      int r;
      
      va_start(pa,fmt);
      r = vfprintf(stream,fmt,pa);
      va_end(pa);
      
      return(r);
    }
  else return(0);
}

int main(void) {
    varargs01(stdout, "%s\n", "hello");
    return 0;
}
