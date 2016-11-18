/* The case expression it casted
 */

int switch05(int predicate)
{
  int x = 0;
  switch (predicate) {
  case (char) 0: x = x;
    break;
  case (char) 10: x = x + 1;
  }
  return x;
}

