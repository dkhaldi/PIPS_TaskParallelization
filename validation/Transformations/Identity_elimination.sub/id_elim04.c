
int id_elim04() {
  int a[1], b[5];
  
  a[0] = 10;
  //useless
  a[0] = a[0];
  
  b[0] = a[0];
  //useless
  b[0] = b[0];
  //not useless
  b[1] = b[0];
  //useless
  b[1] = b[1];
  
  return 0;
}

int main() {
  return id_elim04();
}
