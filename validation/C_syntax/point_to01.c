/* Identify properly structure pointed to by expressions */

void point_to01()
{
  struct s {
    int foo;
  } a, *p;

  (p+2)->foo = 1;

  /* Not floating point pointer arithmetic */
  /* (p+2.)->foo = 1; */

  (p+(int)2.)->foo = 1;
  (2+p)->foo = 1;
  (p-2)->foo = 1;

  /* This one is forbidden */
  /*(2-p)->foo = 1; */

  (p++)->foo = 1;
  (p--)->foo = 1;
  (++p)->foo = 1;
  (--p)->foo = 1;
}
