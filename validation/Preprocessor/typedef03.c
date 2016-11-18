/* Conflict due to the "toto" identifier in PIPS C preprocessor
 */

typedef char toto;

int main() {
  int toto = 0;

  return toto;
}
