#include "freia.h"

freia_status
shuffle_03(freia_data2d * o, const freia_data2d * i)
{
  freia_data2d * t = freia_common_create_data(16, 128, 128);
  freia_data2d * x, * y;
  int32_t vol;
  freia_aipo_add(t, i, i);
  x = t;
  y = i;
  freia_aipo_global_vol(y, &vol);
  freia_aipo_copy(o, x);
  freia_common_destruct_data(t);
  return FREIA_OK;
}
