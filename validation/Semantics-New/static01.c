/* Check setter/getter option combined with a global variable
 */

static int temperature = 0;

void set_temperature(int t)
{
  temperature = t;
}

int get_temperature(void)
{
  int t = temperature;
  return t;
}

int main()
{
  set_temperature(23);
  int t = get_temperature();
  return t;
}
