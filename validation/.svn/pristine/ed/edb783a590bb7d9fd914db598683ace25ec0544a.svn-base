#include "freia.h"

void freia_83(freia_data2d *o, const freia_data2d *i)
{
  const int32_t kernel1x3[9] = {0, 0, 0, 1, 1, 1, 0, 0, 0};
  const int32_t kernel3x1[9] = {0, 1, 0, 0, 1, 0, 0, 1, 0};

  freia_data2d *t = freia_common_create_data(16, 256, 256);

  freia_aipo_erode_8c(t, i, kernel1x3);
  freia_aipo_copy(o, t);
  freia_aipo_erode_8c(t, i, kernel3x1);
  freia_aipo_sup(o, t, o);

  freia_common_destruct_data(t);
}
