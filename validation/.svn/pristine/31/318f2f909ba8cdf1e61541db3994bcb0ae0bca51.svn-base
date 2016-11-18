/* Multiple declarations with a delayed const */

struct s {int mem;};

/* The const is in fact carried by the type: this is illegal C code
 * according to gcc.
 *
 * The PIPS output fixes the issue, but I do not know why. No matter
 * what, this code should not be analyzed by PIPS.
 */

struct s cs = {1}, const vs = {2};
