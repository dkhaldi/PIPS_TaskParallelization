/* Make sure the declaration lists are corrects
 *
 * To be checked in PARSED_CODE
 */

struct s;                          // -> #s -> phv
struct s {int a;};                 // -> #s, phv, #s -> #s
struct s a;                        // -> #s, a -> a
struct s1 { struct s f1; };        // -> #s1, phv, #s -> #s1 
struct s11 { struct s f11; } a1;   // -> #s22, phv, #s1, phv, a1 -> #s11 a1
