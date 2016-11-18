/* Example in C standard for pointer arithmetic linked to VLAs
 *
 * Same as pointer01, except for the assignment to p, just after its
 * declaration. A bug in transformer_inter_full_with_points_to appear
 * in effect_indices_first_pointer_dimension(), effects-util/type.c
 *
 * This is linked to the semantics pointer analysis. Failure in
 * can_be_constant_path_p() called from reference_to_address_entity(),
 * called from pointer_unary_operation_to_transformer().
 *
 * The semantics pointer analysis has not been upgraded to cope
 * properly with points-to. a[0] is not recognized as an address
 * value. It does not appear in proper effects and hence in value
 * mappings.
 *
 * Nevertheless, no core dump is expected. FI is phasing out
 * can_be_constant_path_p() in semantics.
 */

int main(int argc, char ** argv)
{
  int n = 4, m = 3;
  int a[n][m];
  int (*p)[m];
  p = a; // p == &a[0]
  p += 1; // p == &a[1]
  (*p)[2] = 99; // a[1][2] == 99
  n = p - a; // n == 1
  return n;
}
