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

  int _u_a = 1;
  int _u_b = 2;
  scilab_rt_disp_s0_("a = 1   b = 2");
  scilab_rt_disp_s0_("a < b");
  int _tmp0 = (_u_a<_u_b);
  scilab_rt_display_s0i0_("ans",_tmp0);
  scilab_rt_disp_s0_("a <= b");
  int _tmp1 = (_u_a<=_u_b);
  scilab_rt_display_s0i0_("ans",_tmp1);
  scilab_rt_disp_s0_("a == b");
  int _tmp2 = (_u_a==_u_b);
  scilab_rt_display_s0i0_("ans",_tmp2);
  scilab_rt_disp_s0_("a ~= b");
  int _tmp3 = (_u_a!=_u_b);
  scilab_rt_display_s0i0_("ans",_tmp3);
  scilab_rt_disp_s0_("a >= b");
  int _tmp4 = (_u_a>=_u_b);
  scilab_rt_display_s0i0_("ans",_tmp4);
  scilab_rt_disp_s0_("a > b");
  int _tmp5 = (_u_a>_u_b);
  scilab_rt_display_s0i0_("ans",_tmp5);
  scilab_rt_disp_s0_("c = 3.1   d = 3.1");
  double _u_c = 3.1;
  double _u_d = 3.1;
  scilab_rt_disp_s0_("c < d");
  int _tmp6 = (_u_c<_u_d);
  scilab_rt_display_s0i0_("ans",_tmp6);
  scilab_rt_disp_s0_("c <= d");
  int _tmp7 = (_u_c<=_u_d);
  scilab_rt_display_s0i0_("ans",_tmp7);
  scilab_rt_disp_s0_("c == d");
  int _tmp8 = (_u_c==_u_d);
  scilab_rt_display_s0i0_("ans",_tmp8);
  scilab_rt_disp_s0_("c ~= d");
  int _tmp9 = (_u_c!=_u_d);
  scilab_rt_display_s0i0_("ans",_tmp9);
  scilab_rt_disp_s0_("c >= d");
  int _tmp10 = (_u_c>=_u_d);
  scilab_rt_display_s0i0_("ans",_tmp10);
  scilab_rt_disp_s0_("c > d");
  int _tmp11 = (_u_c>_u_d);
  scilab_rt_display_s0i0_("ans",_tmp11);

  scilab_rt_terminate();
}

