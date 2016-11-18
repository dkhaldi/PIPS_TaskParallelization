/* To check the processing of scanf */

#include <stdio.h>

typedef struct
{
	int N1;
  	int N2;
} param;

param q;

void scanf01()
{
  int j;
  param p;

  scanf("%d",&j);
  fscanf(stdin, "%d", &j);

  scanf("%d",&p.N1);
  fscanf(stdin, "%d", &p.N1);

  scanf("%d",&q.N1);
  fscanf(stdin, "%d", &q.N1);

  int r = scanf("%d",&j);
  r = fscanf(stdin, "%d", &j);

  r = scanf("%d",&p.N1);
  r = fscanf(stdin, "%d", &p.N1);

  r = scanf("%d",&q.N1);
  r = fscanf(stdin, "%d", &q.N1);
}
