
int id_elim06() {
  int a[1];
  int *p;
  
  p = a;
  a[0] = 0;
  
  //all normally useless with pointer analisys
  *p = *p;
  *p = a[0];
  a[0] = *p;
  a[0] = a[0];
  
  return a[0];
}

int main() {
  return id_elim06();
}
