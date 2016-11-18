#include "freia.h"

// test with intermediate declaration
freia_status
freia_81(freia_data2d * o, const freia_data2d * i0, const freia_data2d * i1)
{
  freia_aipo_add(o, i0, i1);
  freia_data2d * tmp = freia_common_create_data(16, 128, 128);
  freia_aipo_sub(tmp, o, i1);
  freia_aipo_copy(o, tmp);
  freia_common_destruct_data(tmp);
  return FREIA_OK;
}
