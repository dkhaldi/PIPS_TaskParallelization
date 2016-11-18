/* returns number of chars added to escape "'"s and "\"s in s */
/* slen number of characters in s will be escaped */
/* destination must be long enough for additional chars */
int esc_q(register char *d, register char *s, register int slen)
{
  register int ret = 0;

  while (slen > 0) {
    switch (*s) {
    case '\'':
    case '\\':
      *d = '\\';
      ++d; ++ret;
    case '\"':
    case '\?':
      *d = '\\';
      ++d; ++ret;
    default:
      *d = *s;
      ++d; ++s; --slen;
      break;
    }
  }
  return ret;
}

int main() {
  char d, s;
  int slen;
  esc_q(&d, &s, slen);
  return 0;
}