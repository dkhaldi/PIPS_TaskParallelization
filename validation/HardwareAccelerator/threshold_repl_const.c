#include "freia.h"

int main(int argc, char *argv[]) {
  freia_initialize(argc, argv);
  freia_dataio fdin, fdout;
  freia_common_open_input(&fdin, 0);
  freia_common_open_output(&fdout, 0, fdin.framewidth, fdin.frameheight,
                           fdin.framebpp);

  freia_data2d *imin = freia_common_create_data(fdin.framebpp, fdin.framewidth,
                                                fdin.frameheight);
  freia_common_rx_image(imin, &fdin);

  freia_aipo_threshold(imin, imin, 1, 255, true);
  freia_aipo_replace_const(imin, imin, imin, 255);
  freia_common_tx_image(imin, &fdout);

  freia_common_destruct_data(imin);
  freia_common_close_input(&fdin);
  freia_common_close_output(&fdout);
  freia_shutdown();
  return 0;
}
