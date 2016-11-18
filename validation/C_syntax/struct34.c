/* Do we have separate name spaces for struct, union and enum as
 * implemented in PIPS internal representation?
 *
 * The code below is not acceptable for gcc. But is easily represented
 * by PIPS, which has overused special characters to distinguish
 * between different kinds of derived entities. The distinction should
 * be made thru the type or thru the entity kind.
 */

struct s {int i;};

union s {int i;}; 

enum s {i};
