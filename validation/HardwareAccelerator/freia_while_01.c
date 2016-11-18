#include "freia.h"

int freia_while_01(void) {
  freia_dataio fdin, fdout;
  freia_data2d *in, *out;

  freia_common_open_input(&fdin, 0);
  freia_common_open_output(&fdout, 0, fdin.framewidth, fdin.frameheight,
                           fdin.framebpp);

  in = freia_common_create_data(fdin.framebpp, fdin.framewidth,
                                fdin.frameheight);
  out = freia_common_create_data(fdin.framebpp, fdin.framewidth,
                                 fdin.frameheight);

  // input
  freia_common_rx_image(in, &fdin);

  int i = 0;
  while (i++ < 10) {
    freia_data2d *w1 =
        freia_common_create_data(in->bpp, in->widthWa, in->heightWa);

    freia_aipo_set_constant(w1, w1->bpp == 16 ? 32767 : 255);
    freia_aipo_inf(w1, w1, in);
    freia_aipo_inf(w1, w1, in);
    freia_aipo_inf(out, w1, in);

    freia_common_destruct_data(w1);
  }

  // output
  freia_common_tx_image(in, &fdout);
  freia_common_tx_image(out, &fdout);

  // cleanup
  freia_common_destruct_data(in);
  freia_common_destruct_data(out);

  freia_common_close_input(&fdin);
  freia_common_close_output(&fdout);

  return 0;
}
