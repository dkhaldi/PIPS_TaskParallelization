/* Simplified version of io01
 *
 * Make sure that size_t is defined before 
*/
struct _IO_FILE ;
typedef unsigned int size_t;
struct _IO_FILE {
  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
};
