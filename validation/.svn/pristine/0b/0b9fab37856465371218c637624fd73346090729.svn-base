#include "freia.h"

void freia_82(freia_data2d *imout, const freia_data2d *imin)
{
  const int32_t kernel1x3[9] = {0, 0, 0, 1, 1, 1, 0, 0, 0};
  const int32_t kernel3x1[9] = {0, 1, 0, 0, 1, 0, 0, 1, 0};

  freia_data2d *tmp = freia_common_create_data(16, 256, 256);

  freia_aipo_erode_8c(tmp, imin, kernel1x3);
  freia_aipo_set_constant(imout, 0);
  freia_aipo_sup(imout, tmp, imout);
  freia_aipo_erode_8c(tmp, imin, kernel3x1);
  freia_aipo_sup(imout, tmp, imout);

  freia_common_destruct_data(tmp);
}
