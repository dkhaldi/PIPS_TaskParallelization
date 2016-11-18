#include "bench.h"
/*
 * benchmark program:   lms.c
 * 
 * benchmark suite:     DSP-kernel
 * 
 * description:         lms - filter benchmarking
 *
 *  
 *               x(n-0)  ---- x(n-1)  ----- x(n-i) -----  x(n-N+1)
 *    x(n) --->---------| 1/z|-------| 1/z|-.....-| 1/z|----
 *                  |   -----    |   ------   |   ------   |
 *                  h0           h1           hi          hN-1
 *                    \________  |____   _____|  _________/
 *                             \______(+)_______/
 *                                     |
 *                                     |---------> y(n)
 *                                     v
 *          d(n) -------------------->(+)--------> e(n)
 *                                   -
 * 
 * 
 * Notation and symbols:
 * x(n)  - Input sample at time n.
 * d(n)  - Desired signal at time n.
 * y(n)  - FIR filter output at time n.
 * H(n)  - Filter coefficient vector at time n.  H={h0,h1,..,hN-1}
 * X(n)  - Filter state variable vector at time N.
 *         X={x(0),x(n-1),...,x(n-N+1)}
 * delta - Adaptation gain.
 * N     - Number of coefficient taps in the filter. 
 * 
 * PROCESSING:
 *
 *     True LMS Algorithm       
 *     ------------------       
 *     Get input sample         
 *     Save input sample        
 *     Do FIR                   
 *     Shift vector X           
 *     Get d(n), calculate e(n)      
 *     Update coefficients      
 *     Output y(n)              
 *
 *
 * System equations:
 * 
 * e(n)  = d(n) - H(n)  X(n)       (FIR filter and error)
 * H(n+1)= H(n) + delta X(n) e(n)  (Coefficient update)
 * 
 * References:
 *  "Adaptive Digital Filters and Signal Analysis", Maurice G. Bellanger
 *     Marcel Dekker, Inc. New York and Basel
 *  
 *  "The DLMS Algorithm Suitable for the Pipelined Realization of Adaptive
 *      Filters", Proc. IEEE ASSP Workshop, Academia Sinica, Beijing, 1986
 *
 *
 * 
 * reference code:      target assembly
 * 
 * f. verification:     none
 * 
 *  organization:        Aachen University of Technology - IS2 
 *                       DSP Tools Group
 *                       phone:  +49(241)807887 
 *                       fax:    +49(241)8888195
 *                       e-mail: zivojnov@ert.rwth-aachen.de 
 *
 * author:              Juan Martinez Velarde
 * 
 * history:             29-3-94 creation (Martinez Velarde)
 *                      03-4-94 first revision, optimized (Martinez Velarde)
 *
 *                      $Author: DSPstone $
 *                      $Date: 1995/04/11 07:33:10 $
 *                      $Revision: 1.2 $  
 */

#define STORAGE_CLASS  register
#define TYPE           float


#define N 16  /* number of coefficient taps */


void
pin_down(TYPE *d, TYPE *x, TYPE *delta, TYPE H[N], TYPE X[N])
{
  int f ; 

  *d = 7 ; 
  *x = 8 ;
  *delta = 1 ; 
  
  for (f = 0 ; f < N ; f++) 
    {
      H[f] = 1 ; 
      X[f] = 1 ; 
    }

}

TYPE
main()
{ 
  static TYPE H[N] ; /* Filter Coefficient Vector */
  static TYPE X[N] ; /* Filter State Variable Vector */
  
  TYPE delta  ;  /* Adaption Gain */
  TYPE d ;       /* Desired signal */
  TYPE x ;       /* Input Sample */
  TYPE y ;       /* FIR LMS Filter Output */
  STORAGE_CLASS TYPE error ;   /* FIR error */
  
  int f ; 
  
  
  pin_down(&d,&x,&delta,H,X) ;
  
  START_PROFILING; 
  
  y = 0 ; 
  
  /* FIR filtering and State Variable Update */
  
  for (f = 1 ; f < N  ; f++)
    y += H[N-1-f] * (X[N-1-f] = X[N-2-f]) ;  
  
  /* last convolution tap, get input sample */
  
  y += H[0] * (X[0] = x)  ;      
  
  /* 
   *  error as the weighted difference 
   *  between desired and calculated signal 
   *
   */
  
  error = (d - y) * delta ; 
  
  for (f =  0; f < N ; f++) 
    H[f] += error * X[f] ;   /* update the coefficients */ 
  
  END_PROFILING; 
  
  pin_down(&d,&x,&y,H,X) ; 
  
  return(0)  ; 
  
}

