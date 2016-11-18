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

void foo__i0i0(int* _u_x, int* _u_y)
{
  *_u_x = 1;
  *_u_y = 2;
}



/*----------------------------------------------------*/

int main(int argc, char* argv[])
{
  scilab_rt_init(argc, argv, COLD_MODE_STANDALONE);

  /*  t97.sce - user function returning tuple */
  int _u_a;
  int _u_b;
  foo__i0i0(&_u_a,&_u_b);
  scilab_rt_display_s0i0_("b",_u_b);
  scilab_rt_display_s0i0_("a",_u_a);

  scilab_rt_terminate();
}

