/* Bug in struct assignment to array element
 *
 * Excerpt from struct26.c
 *
 * Submitted by Corinne Ancourt
 */

typedef struct {
  float   x;
  float   y;
} complexfloat;

complexfloat F2(complexfloat a)
{
  complexfloat ret;
  ret = a;
  return ret;
}

void FM(int np,  complexfloat in[np], complexfloat out[np])
{
  int p;
  for (p = 0; p < np; p++)  {
    out[p] = F2(out[p]);	
  }
}

