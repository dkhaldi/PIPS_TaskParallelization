
#include <stdio.h>
#include <stdlib.h>

void scilab_rt_interp1_d2d2d2_d2(int sin00, int sin01, double in0[sin00][sin01],
    int sin10, int sin11, double in1[sin10][sin11],
    int sin20, int sin21, double in2[sin20][sin21],
    int sout00, int sout01, double out0[sout00][sout01])
{
  int i;
  int j;

  double val0 = 0;
  double val1 = 0;
  double val2 = 0;
  for (i = 0; i < sin00; ++i) {
    for (j = 0; j < sin01; ++j) {
      val0 += in0[i][j];
    }
  }

  for (i = 0; i < sin10; ++i) {
    for (j = 0; j < sin11; ++j) {
      val1 += in1[i][j];
    }
  }

  for (i = 0; i < sin20; ++i) {
    for (j = 0; j < sin21; ++j) {
      val2 += in2[i][j];
    }
  }

  for (i = 0; i < sout00; ++i) {
    for (j = 0; j < sout01; ++j) {
        out0[i][j] = val0 + val1 + val2;
    }
  }
}
