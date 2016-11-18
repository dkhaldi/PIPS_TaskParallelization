/*
 * (c) HPC Project - 2010-2011 - All rights reserved
 *
 */

#include "scilab_rt.h"


int __lv0;
int __lv1;
int __lv2;
int __lv3;

/*----------------------------------------------------*/


/*----------------------------------------------------*/

int main(int argc, char* argv[])
{
  scilab_rt_init(argc, argv, COLD_MODE_STANDALONE);

  double _u_a[3][4];
  _u_a[0][0]=4.0;
  _u_a[0][1]=7;
  _u_a[0][2]=8;
  _u_a[0][3]=6;
  _u_a[1][0]=4;
  _u_a[1][1]=6;
  _u_a[1][2]=7;
  _u_a[1][3]=3;
  _u_a[2][0]=10;
  _u_a[2][1]=2;
  _u_a[2][2]=3;
  _u_a[2][3]=8;
  int _u_b[4][2];
  _u_b[0][0]=1;
  _u_b[0][1]=10;
  _u_b[1][0]=4;
  _u_b[1][1]=7;
  _u_b[2][0]=1;
  _u_b[2][1]=7;
  _u_b[3][0]=3;
  _u_b[3][1]=7;
  double _tmp0[3][2];
  scilab_rt_mul_d2i2_d2(3,4,_u_a,4,2,_u_b,3,2,_tmp0);
  scilab_rt_display_s0d2_("ans",3,2,_tmp0);

  scilab_rt_terminate();
}

