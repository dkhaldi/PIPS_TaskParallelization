/* Make sure that a struct is properly declared */

struct x
{
  int a:1;
  signed int b:2;
  unsigned c:3;
  long int d:4;
  char e:5;
  signed :6;
};

// } y;
