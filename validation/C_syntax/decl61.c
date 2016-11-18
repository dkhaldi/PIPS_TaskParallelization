/* Goal: check warnings related to a statement spread over several lines
 *
 * Excerpt of Semantics/loop03.c
 *
 * Issue: the warning is wrong... No attempt should be made to create
 * return value: it is too early in the parser. Furthermore, a void
 * function does not need a return value.
 */

//#include <stdlib.h>
//#include <stdio.h>
/* To have M_PI: */
//#define _GNU_SOURCE
//#include <math.h>

#define N 64
#define M 256

typedef float f_float_t;

typedef struct	{
		float re;
		float im;
		} complex;

float imagein_re[N][N], imageout_re[M][M];
float imagein_im[N][N], imageout_im[M][M];


void decl61(fn)

     char * fn;

{	extern complex imagein[N][N], imageout[M][M];
}
