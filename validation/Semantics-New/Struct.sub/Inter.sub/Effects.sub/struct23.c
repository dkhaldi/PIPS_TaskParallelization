/* Bug with struct assignment
 *
 * Same as struct22, but with non constant subscript expressions
 */

typedef struct
{
	int N1;
	int N2;
} param;


param p[10];

int main(int argc, char* argv[])
{
  int i, j;
  p[i]=p[j];
  return (0);
}

