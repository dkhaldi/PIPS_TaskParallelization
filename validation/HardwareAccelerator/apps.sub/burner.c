#include <stdio.h>
#include "freia.h"

void transposeNeighbor(int32_t neighborOut[9], const int32_t neighborIn[9])
{
  int i;
  for(i=0; i < 9; i++) {
    neighborOut[8-i] = neighborIn[i];
  }
}

static const int32_t freia_morpho_k8_0[9] = {0, 0, 0, 1, 1, 1, 0, 0, 0};
static const int32_t freia_morpho_k8_1[9] = {0, 1, 0, 0, 1, 0, 0, 1, 0};
static const int32_t freia_morpho_k8_2[9] = {0, 0, 1, 0, 1, 0, 1, 0, 0};

int main(int argc, char *argv[])
{
   freia_dataio fdin, fdout;
   freia_data2d *imin, *in, *imTophat, *imClose, *imZone1, *imZone2, *imZone3, *imWork1, *out;

   static const  int32_t freia_morpho_k8_center_east[9] = {0, 0, 0, 0, 1, 1, 0, 0, 0};
   static const  int32_t freia_morpho_k8_center_north[9] = {0, 1, 0, 0, 1, 0, 0, 0, 0};
   int32_t neighborTransposed_0[9];
   int32_t neighborTransposed_1[9];
   register int32_t volprevious;
   int32_t volcurrent;

   // there should be a freia_initialize()? yup we should have one for opencl
   // 1st arg: 1=GPU, 2=CPU, 2nd arg sub-device
   freia_initialize(argc, argv);
   freia_common_open_input(&fdin, 0);
   freia_common_open_output(&fdout, 0, fdin.framewidth, fdin.frameheight, fdin.framebpp);

   imin = freia_common_create_data(fdin.framebpp, fdin.framewidth, fdin.frameheight);
   in = freia_common_create_data(fdin.framebpp, fdin.framewidth, fdin.frameheight);
   imClose = freia_common_create_data(fdin.framebpp, fdin.framewidth, fdin.frameheight);
   imTophat = freia_common_create_data(fdin.framebpp, fdin.framewidth, fdin.frameheight);
   imZone1 = freia_common_create_data(fdin.framebpp, fdin.framewidth, fdin.frameheight);
   imZone2 = freia_common_create_data(fdin.framebpp, fdin.framewidth, fdin.frameheight);
   imZone3 = freia_common_create_data(fdin.framebpp, fdin.framewidth, fdin.frameheight);

   imWork1 = freia_common_create_data(fdin.framebpp, fdin.framewidth, fdin.frameheight);
   out = freia_common_create_data(fdin.framebpp, fdin.framewidth, fdin.frameheight);

   // input
   freia_common_rx_image(imin, &fdin);
   freia_aipo_copy(in, imin);

   freia_common_draw_rect(in, in->xStartWa, in->yStartWa, in->xStartWa+in->widthWa-1, in->yStartWa+in->heightWa-1, 255);

   // Closing
   transposeNeighbor(neighborTransposed_0, freia_morpho_k8_center_east);

   freia_aipo_dilate_8c(imWork1, in, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);
   freia_aipo_dilate_8c(imWork1, imWork1, freia_morpho_k8_center_east);

   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);
   freia_aipo_erode_8c(imWork1, imWork1, neighborTransposed_0);

   transposeNeighbor(neighborTransposed_1, freia_morpho_k8_center_north);

   freia_aipo_dilate_8c(out, in, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);
   freia_aipo_dilate_8c(out, out, freia_morpho_k8_center_north);

   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);
   freia_aipo_erode_8c(out, out, neighborTransposed_1);

   freia_aipo_inf(imClose, imWork1, out);
   freia_aipo_sub(imTophat, imClose, imin);

   freia_aipo_threshold(imZone1, imTophat, 105, 255, 1);
   freia_aipo_threshold(imZone2, imTophat, 60, 105, 1);
   freia_aipo_threshold(imZone3, imClose, 100, 150, 1);

   freia_aipo_sup(imWork1, imZone1, imZone2);
   freia_aipo_sup(imWork1, imWork1, imZone3);
   freia_aipo_not(imWork1, imWork1);

   freia_aipo_dilate_8c(out, imWork1, freia_morpho_kernel_8c);
   freia_aipo_dilate_8c(out, out, freia_morpho_kernel_8c);

   freia_aipo_global_vol(out, &volcurrent);
   do {
      volprevious = volcurrent;
      freia_aipo_erode_8c(out, out, freia_morpho_kernel_8c);
      freia_aipo_sup(out, out, imWork1);
      freia_aipo_global_vol(out, &volcurrent);
   }
   while (volcurrent!=volprevious);

   // Change  pixel values for the display
   freia_aipo_inf_const(imZone1, imZone1, 40);
   freia_aipo_inf_const(imZone2, imZone2, 100);
   freia_aipo_inf_const(imZone3, imZone3, 170);
   freia_aipo_inf_const(out, out, 250);

   freia_aipo_sup(imWork1, imZone2, imZone1);
   freia_aipo_sup(imWork1, imZone3, imWork1);
   freia_aipo_sup(out, out, imWork1);

   // output
   freia_common_tx_image(imin, &fdout);
   freia_common_tx_image(out, &fdout);

   // cleanup
   freia_common_destruct_data(imin);
   freia_common_destruct_data(in);
   freia_common_destruct_data(imTophat);
   freia_common_destruct_data(imClose);
   freia_common_destruct_data(imZone1);
   freia_common_destruct_data(imZone2);
   freia_common_destruct_data(imZone3);
   freia_common_destruct_data(imWork1);
   freia_common_destruct_data(out);

   freia_common_close_input(&fdin);
   freia_common_close_output(&fdout);

   freia_shutdown();
   return 0;
}
