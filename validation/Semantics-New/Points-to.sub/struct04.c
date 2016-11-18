/* Check one access via a pointer to a struct
 *
 * Intraprocedural
 */

struct Mastruct {
  int first;
  char second;
};

struct Sastruct {
  struct Mastruct * p;
};

int main()
{
  struct Mastruct toto;
  struct Sastruct riri = {&toto};

  toto.first = 0;
  riri.p->first = 1;
  
  return 0;
}
