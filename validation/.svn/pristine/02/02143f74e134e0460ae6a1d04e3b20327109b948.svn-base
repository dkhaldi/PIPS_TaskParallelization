/* Bug in struct assignment to return values
 *
 * Submitted by Corinne Ancourt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  float   x;
  float   y;
} complexfloat;


complexfloat X1[10];
complexfloat X2[10]; 

complexfloat F1(complexfloat a)
{
  complexfloat r;
  r.x = -(a).y;
  r.y = a.x;
  return r;
}

complexfloat F2(complexfloat a, complexfloat b)
{
  complexfloat ret;
  ret.x = -(a).y * (b).y + (a).x * (b).x;
  ret.y = (a).y * (b).x + (a).x * (b).y;
  return ret;
}

void FM(int np,  complexfloat in[np], complexfloat out[np])
{
  int p;
  int i, j;
  complexfloat tmp;			
  tmp.x = 0.1;			
  tmp.y =  1.;			
  for (p = 0; p < np; p++) {
    out[p].x = in[p].x;
    out[p].y = in[p].y;
  }
  for (p = 0; p < np; p++)  {
    out[p] = F2(out[p], tmp);	
  }
}

void main()
{
 FM(10, X1, X2);
}

