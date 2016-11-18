/* Example submitted by mikhail.ramalho@gmail.com
 *
 * Same as unsigned09.c, but the property
 * SEMANTICS_USE_TYPE_INFORMATION is used.
 *
 * Hence, transformers for sn+=2 and i++ become fuzzy and no useful
 * result is obtained.
 *
 * Since i<n, i++ does not generate a wrap around on i if the loop is
 * entered.
 *
 * But the same property is not true for sn which may wrap around. The
 * invariant between i and sn, namely sn==2i, is only true when n is
 * less than half the magnitude of the type, here around two billions.
 *
 * With n unknown, and using unsigned char to make it easier, sn may
 * have any value between 0 and 254 in the loop and in the loop
 * postcondition. sn==2i or sn==2i-256 and i==n, since the loop is
 * either entered or i==n==0.
 */

int main() { 
  unsigned int sn = 0;
  unsigned int i = 0;
  unsigned int n;

  while (i < n)
  {
    sn = sn + 2;
    i++;
  }

  return 0;
}

