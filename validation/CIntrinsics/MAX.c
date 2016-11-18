/* MAX is identified as the Fortran intrinsics MAX and not as a C
 * function as it should here.
 *
 * The C parser (the parsers) should check the language of the intrinsics.
 */

int main() {
    int a;
    a = MAX(1,2);
    return 0;
}
