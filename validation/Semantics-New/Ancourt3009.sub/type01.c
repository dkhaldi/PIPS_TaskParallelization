/* Detection of a type conflict between formal and actual arguments of "update"
 */

unsigned int v;

void update(int *p)
{
  *p = 3;
}

int main(int argc, char * argv[])
{
  update(&v);
  return (int) v;
}
