/* Bug in preprocessor because of "s" in "struct s struct23()" before
 * "struct23" (Ticket 298).
 *
 * Another issue: "struct s" must be analyzed before "struct23()",
 * when no current module is yet defined.
 */

struct s {
  int in;
};

struct s struct23()
{
  struct s s;
  s.in = 0;
  return s;
}
