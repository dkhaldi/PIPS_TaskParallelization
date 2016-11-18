/* Case provided by Benoit Pin: where to declare struct entities ? */

typedef struct arc *arc_p;

struct arc
{
  int cost;
  arc_p a;
};
