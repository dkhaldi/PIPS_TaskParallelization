/* p is used uninitialized and this is detected by gcc */

void dereferencing05()
{
  double * p;
  int i;

  *(p++) = 0.;
  *(p--) = 0.;
  *(++p) = 0.;
  *(--p) = 0.;
  return;
}
