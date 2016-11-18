/* Bug with struct formal argument and struct assignment to return value
 *
 * 
 */

typedef struct
{
	int N1;
	int N2;
} param;


param copy(param s) {
  return s;
}


int main(int argc, char* argv[])
{
  int i = 1, j = 2;
  param pi, po;
  pi.N1 = i;
  pi.N2 = j;
  po = copy(pi);
  return (0);
}
