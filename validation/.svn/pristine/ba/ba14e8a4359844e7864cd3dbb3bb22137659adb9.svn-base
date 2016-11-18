/* Bug with struct assignment using array elements with constant subscripts
 */
 
typedef struct
{
	int N1;
	int N2;
} param;


param p[10];

int main(int argc, char* argv[])
{
  //p[2].N1 = 1;
  //p[2].N2 = 2;
  p[1]=p[2];
  return (0);
}

