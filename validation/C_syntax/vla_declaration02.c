/* Declaration of a VLA as formal argument using a pointer
 * dereferencing, the pointer being another formal argument.
 *
 * Modified version of vla_declaration01: function definition instead
 * of function declaration.
 *
 * Such a bug was found in a piece of code written by Fabien Coelho,
 * but it is not reproduced in this much simpler setting.
 */

typedef struct {int dim;} param;

void vla_declaration02(param *p, double a[p->dim])
{
}
