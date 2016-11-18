/* Bug with struct assignment to return value
 *
 * 
 */

typedef struct
{
	int N1;
	int N2;
} param;

param init(int n1, int n2) {
  param s;
  s.N1 = n1;
  s.N2 = n2;
  return s;
}

int main(int argc, char* argv[])
{
  int i = 1, j = 2;
  param p;
  p = init(i,j);
  return p.N1;
}
