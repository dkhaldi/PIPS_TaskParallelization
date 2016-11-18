/* Same code as call02c, but longer tpips script
 *
 * Results are wrong, but no core dump.
 *
 * Values projected because of translation errors in semantics:
 *
 * Value "update_sub:_sub1_1[0][var2]" is projected. Call from "update_s3":
 *
 * 	update_sub(&(a->s3)[i]);
 *
 */

typedef struct {
  int var2;
} sub;

typedef struct {
  sub s1;
  sub s2[3][2];
  sub s3[4];
} content;

void update_sub(sub *sub1){
  sub1->var2=3;
  return;
}

void update_s3(content* a) {
  for(int i = 0; i<4;i++) {
    update_sub(&(a->s3[i]));
  }
  update_sub(&(a->s3[2]));
  return;
}
