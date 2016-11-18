#include <stdio.h>

int esc(register char *d, register char *s, register int slen)
{
  register int ret = 0;

  while (slen > 0) {
    switch (*s) {
    //Octal
    case '\101':
      printf("A\n");
      break;
    //hexa
    case '\x42':
      printf("B\n");
      break;
    //unicode
    case '\u1234':
      printf("...\n");
      break;
    //unicode
    case '\U12345678':
      printf("...\n");
      break;
    default:
      break;
    }
  }
  return ret;
}

int main() {
  char d, s;
  int slen = 0;
  esc(&d, &s, slen);
  return 0;
}
