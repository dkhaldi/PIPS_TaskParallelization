// PIPS management of C intrinsics by the prettyprinter: normalize MIN
// for C with pips_min or preserve MIN

int main()
{
  int i = 0, j = 1, k = 2, l;

  l = MIN(i,j,k);

  return l;
}
