/* Same as array10.c, but with an update operator i n update_array()
 *
 * Bug: not implemented yet...
 */

void update_array(int a[3][3][3])
{
  a[0][1][2] += 12; // FI: Not implemented yet...
  return;
}

int main()
{
  struct {
    int a[3][3][6/2];
  } s;


  s.a[0][1][2] = 1;
  update_array(s.a);
  s.a[0][1][2] = 1;

  return 0;
}
