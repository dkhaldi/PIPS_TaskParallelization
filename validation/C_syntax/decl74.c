/* simpler version of ngspice01.c
 * 
 * Uses anonymous structs which may explain the redeclaration of the
 * internal struct...
 */
    
struct {
  union {
    struct {
      int	mult;
    } lin;
  } xaxis;
} grid;
