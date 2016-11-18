//     goal: show effect of cloning, partial evaluation and loop unrolling
//     and reduction parallelization for a Power architecture
//     kernel_size must be odd

#include <stdio.h>
#include <stdlib.h>

#define kernel_size 3
#define nsteps 10

void convol3x3();

int main(int argc, char **argv) //      program image_processing
{
    int image_size = argc > 1 ? atoi(argv[1]): 100;
    float (*image)[image_size][image_size];
    float (*new_image)[image_size][image_size];
    float kernel[kernel_size][kernel_size];
    int i, j, n;
    image = malloc(sizeof(float)*image_size*image_size);
    new_image = malloc(sizeof(float)*image_size*image_size);


    for( i = 0; i< kernel_size; i++) {
        for( j = 0; j< kernel_size; j++) {
            kernel[i][j] = 1;
        }
    }

    //     read *, image
    for( i = 0; i< image_size; i++) {
        for( j = 0; j< image_size; j++)
            (*image)[i][j] = 1.;
    }


    for( n = 0; n< nsteps; n++) {
        convol3x3(image_size, image_size, *new_image, *image,
                kernel);
    }

    for( i = 0; i< image_size; i++) { 
        printf("%f ",(*new_image)[i][i]); 
    } 
    free(image);
    free(new_image);
    //     print *, new_image
    //      print *, new_image (image_size/2, image_size/2)

    return 0; 
}

void convol3x3(int isi, int isj, float new_image[isi][isj], float image[isi][isj], 
        float kernel[kernel_size][kernel_size])
{
    //     The convolution kernel is not applied on the outer part
    //     of the image

    int i, j,k,l;

    for(i = 0; i< isi; i++) {
        for(j = 0; j< isj; j++) {
            new_image[i][j] = image[i][j];
        }
    }

    for(i =  kernel_size/2; i<isi - kernel_size/2; i++) {
        for(j =  kernel_size/2; j<isj - kernel_size/2; j++) {
            new_image[i][j] = 0.;
            for(k=0;k<kernel_size;k++)
            for(l=0;l<kernel_size;l++)
            new_image[i][j] += image[i+k-kernel_size/2][j+l-kernel_size/2]* kernel[k][l];
            new_image[i][j] = new_image[i][j]/(kernel_size*kernel_size);
        }
    }
}
