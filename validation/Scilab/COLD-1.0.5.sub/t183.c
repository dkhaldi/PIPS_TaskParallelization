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

  /*  t183.sce: read_*type*_from_scilab function */
  /*  scilab */
  char* __cmd0[4]={
    "s_int     = 42",
    "s_real    = 42.24",
    "s_complex = 2 + 3*%i",
    "s_string  = \"titi\""};
      scilab_rt_send_to_scilab_s1_(4,__cmd0);
  /*  endscilab */
  int _u_user_int = scilab_rt_read_int_from_scilab_s0_("s_int");
  scilab_rt_display_s0i0_("user_int",_u_user_int);
  double _u_user_real = scilab_rt_read_real_from_scilab_s0_("s_real");
  scilab_rt_display_s0d0_("user_real",_u_user_real);
  double complex _u_user_complex = scilab_rt_read_complex_from_scilab_s0_("s_complex");
  scilab_rt_display_s0z0_("user_complex",_u_user_complex);
  char* _u_user_string = scilab_rt_read_string_from_scilab_s0_("s_string");
  scilab_rt_display_s0s0_("user_string",_u_user_string);
  /*  scilab */
  char* __cmd1[4]={
    "m_int     = [1 2 3 4; 5 6 7 8]",
    "m_real     = [1.1 2.2 3.3 4.4; 5.5 6.6 7.7 8.8]",
    "m_complex = [1 + (2*%i), 3 + (4*%i) ; 5 + (6*%i), 7 + (8*%i)]",
    "m_string  = [\"foo\", \"bar\" ; \"quux\", \"titi\"]"};
      scilab_rt_send_to_scilab_s1_(4,__cmd1);
  /*  endscilab */
  int _u_user_intM[2][4];
  scilab_rt_read_intM_from_scilab_s0i0i0_i2("m_int",2,4,2,4,_u_user_intM);
  scilab_rt_display_s0i2_("user_intM",2,4,_u_user_intM);
  double _u_user_realM[2][4];
  scilab_rt_read_realM_from_scilab_s0i0i0_d2("m_real",2,4,2,4,_u_user_realM);
  scilab_rt_display_s0d2_("user_realM",2,4,_u_user_realM);
  double complex _u_user_complexM[2][2];
  scilab_rt_read_complexM_from_scilab_s0i0i0_z2("m_complex",2,2,2,2,_u_user_complexM);
  scilab_rt_display_s0z2_("user_complexM",2,2,_u_user_complexM);
  char* _u_user_stringM[2][2];
  scilab_rt_read_stringM_from_scilab_s0i0i0_s2("m_string",2,2,2,2,_u_user_stringM);
  scilab_rt_display_s0s2_("user_stringM",2,2,_u_user_stringM);

  scilab_rt_terminate();
}

