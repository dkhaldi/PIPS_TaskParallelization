void foofoo(void) {}
void foobla(void) {}
void blabla(void) {}
void foo(void) { foofoo(); foobla(); }
void bla(void) { blabla(); }
void stuff(void) { foo(); }

int main(void)
{
  foo();
  bla();
  stuff();
  return 0;
}
