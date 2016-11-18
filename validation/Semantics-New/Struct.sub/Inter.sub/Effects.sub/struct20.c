// Problem with array declaration with struct fields


typedef struct
{
	int N1;
	int N2;
	int N3;
	int N4;
	int N5;
} param;

param p;

int init()
{
  p.N1 =1;
  p.N2 =1;
  p.N3 =1;
  p.N4 =1;
  p.N5 =1;
}
void struct20()
{
  while(init()) {
    int A[p.N4][p.N3][p.N1];
  }
  return;
}
