
//void comment_before_test(int a, int b)
void comment11(int a, int b)
{
  do {
  //Shouldn't be lost
  // but use to be because of the ?: syntax in the test
  } while (a<((b<0)?1:2));
}

