// A> Marechal & al., Polyhedral approximation of multivariate polynomials using Handelmans theorem
// VMCAI 2016, pp. 166-184

// Not much information is derived by PIPS because sums of squares are
// not precisely analyzed: x<=2 is not found

int main(void)
{
  int x, y, z;
  if(x>=1 && y>=-2 && x>=y && x <= 5-y) {
    if(x*x+y*y<=4)
      z = y*x;
    else
      z = 0;
  }
  return 0;
}
