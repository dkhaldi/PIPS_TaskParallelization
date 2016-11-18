// global/private with casts

void global_one(float * a)
{
  * (float *) a = 1.0;
}

void private_one(float * a)
{
  * (float *) a = 1.0;
}

void casts01(float * a)
{
  float l[10];
  for (int i = 0; i < 10; i++)
  {
    float * p = (float *) (a + i);
    global_one(p);
    float * q = (float *) & l[i];
    private_one(q);
  }
}

int main(void)
{
  float a[10];
  casts01(a);
  return 0;
}
