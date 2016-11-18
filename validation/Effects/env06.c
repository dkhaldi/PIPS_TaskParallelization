/* To check behavior of global variable in the environment */
int g;

int env06()
{
  g=0;
  return g;
}

int main()
{
  return env06();
}
