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

  /*  t215.sce: RT, left divide  */
  double _u_a1[3][3];
  _u_a1[0][0]=1.0;
  _u_a1[0][1]=(-1);
  _u_a1[0][2]=2;
  _u_a1[1][0]=3;
  _u_a1[1][1]=2;
  _u_a1[1][2]=1;
  _u_a1[2][0]=2;
  _u_a1[2][1]=(-3);
  _u_a1[2][2]=5;
  scilab_rt_display_s0d2_("a1",3,3,_u_a1);
  double _u_b1[3][5];
  _u_b1[0][0]=1.0;
  _u_b1[0][1]=5;
  _u_b1[0][2]=3;
  _u_b1[0][3]=8;
  _u_b1[0][4]=1;
  _u_b1[1][0]=1;
  _u_b1[1][1]=3;
  _u_b1[1][2]=2;
  _u_b1[1][3]=7;
  _u_b1[1][4]=4;
  _u_b1[2][0]=9;
  _u_b1[2][1]=3;
  _u_b1[2][2]=8;
  _u_b1[2][3]=3;
  _u_b1[2][4]=1;
  scilab_rt_display_s0d2_("b1",3,5,_u_b1);
  double _u_x1[3][5];
  scilab_rt_leftdivide_d2d2_d2(3,3,_u_a1,3,5,_u_b1,3,5,_u_x1);
  scilab_rt_display_s0d2_("x1",3,5,_u_x1);
  double _u_c1[3][5];
  scilab_rt_mul_d2d2_d2(3,3,_u_a1,3,5,_u_x1,3,5,_u_c1);
  scilab_rt_display_s0d2_("c1",3,5,_u_c1);
  int _u_a2[3][3];
  _u_a2[0][0]=1;
  _u_a2[0][1]=(-1);
  _u_a2[0][2]=2;
  _u_a2[1][0]=3;
  _u_a2[1][1]=2;
  _u_a2[1][2]=1;
  _u_a2[2][0]=2;
  _u_a2[2][1]=(-3);
  _u_a2[2][2]=5;
  scilab_rt_display_s0i2_("a2",3,3,_u_a2);
  int _u_b2[3][5];
  _u_b2[0][0]=1;
  _u_b2[0][1]=5;
  _u_b2[0][2]=3;
  _u_b2[0][3]=8;
  _u_b2[0][4]=1;
  _u_b2[1][0]=1;
  _u_b2[1][1]=3;
  _u_b2[1][2]=2;
  _u_b2[1][3]=7;
  _u_b2[1][4]=4;
  _u_b2[2][0]=9;
  _u_b2[2][1]=3;
  _u_b2[2][2]=8;
  _u_b2[2][3]=3;
  _u_b2[2][4]=1;
  scilab_rt_display_s0i2_("b2",3,5,_u_b2);
  double _u_x2[3][5];
  scilab_rt_leftdivide_i2i2_d2(3,3,_u_a2,3,5,_u_b2,3,5,_u_x2);
  scilab_rt_display_s0d2_("x2",3,5,_u_x2);
  double _u_c2[3][5];
  scilab_rt_mul_i2d2_d2(3,3,_u_a2,3,5,_u_x2,3,5,_u_c2);
  scilab_rt_display_s0d2_("c2",3,5,_u_c2);
  double _u_x3[3][5];
  scilab_rt_leftdivide_d2i2_d2(3,3,_u_a1,3,5,_u_b2,3,5,_u_x3);
  scilab_rt_display_s0d2_("x3",3,5,_u_x3);
  double _u_c3[3][5];
  scilab_rt_mul_d2d2_d2(3,3,_u_a1,3,5,_u_x3,3,5,_u_c3);
  scilab_rt_display_s0d2_("c3",3,5,_u_c3);
  double _u_x4[3][5];
  scilab_rt_leftdivide_i2d2_d2(3,3,_u_a2,3,5,_u_b1,3,5,_u_x4);
  scilab_rt_display_s0d2_("x4",3,5,_u_x4);
  double _u_c4[3][5];
  scilab_rt_mul_i2d2_d2(3,3,_u_a2,3,5,_u_x4,3,5,_u_c4);
  scilab_rt_display_s0d2_("c4",3,5,_u_c4);

  scilab_rt_terminate();
}

