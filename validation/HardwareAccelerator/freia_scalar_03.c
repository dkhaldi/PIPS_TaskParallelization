#include "freia.h"

freia_status
  freia_scalar_03(freia_data2d * o, freia_data2d * i0, freia_data2d * i1)
{
  freia_data2d * tmp = freia_common_create_data(16, 128, 128);
  int max, min = 10;
  bool bin = false;
  // break pipeline on scalar dependency
  freia_aipo_add(tmp, i0, i1);
  freia_aipo_global_max(tmp, &max);
  freia_aipo_threshold(o, tmp, min, max, bin);
  freia_common_destruct_data(tmp);
  return FREIA_OK;
}
