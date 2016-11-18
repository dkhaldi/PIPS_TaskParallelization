/* Check impact of variable incrementation with wrap-around
 * (i.e. integer overflows). Example given in pipsmake-rc.tex/
 *
 * The transformers must be computed using type information
 */


int foo(unsigned char i, unsigned char j)
{
  int k = 0;
  if(i<j) {
    i++, j++;
    if(i<j)
      // true branch
      k = 1;
    else
      // false branch
      k = 2;
  }
  return k;
}

/* The main below is useful to obtain a precondition with formal
 * parameters in its basis. With a default identity transformer, the
 * value basis is empty and no type information is added.
 *
 * x and y are left uninitialized on purpose.
 */
int main()
{
  unsigned char x, y;
  return foo(x, y);
}
