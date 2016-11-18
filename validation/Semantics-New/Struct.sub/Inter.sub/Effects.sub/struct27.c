/* Make sure that fields with non alayzed types are not assigned in a
 * struct assignment.
 *
 * Simplified version of struct26.c
 */

typedef struct {
  float   x;
  float   y;
} complexfloat;

complexfloat F1(complexfloat a)
{
  complexfloat r;
  r.x = -(a).y;
  r.y = a.x;
  return r;
}
