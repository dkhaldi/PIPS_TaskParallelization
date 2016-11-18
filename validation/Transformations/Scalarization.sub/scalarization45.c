void SetVal(int size, int Out[size], int val)
{
	int i;
	for (i =0; i<size; i++) {
		Out[i] = val;
	}
}

void Add1(int size, int tabIn[size], int tabOut[size])
{
	int i;
	for (i=0 ; i<size; i++) {
		tabOut[i] = tabIn[i] + 1;
	}
}

void Test(int size, int tab[size], int res)
{
	int i;
	for (i =0; i<size; i++) {
		if (tab[i] != res) {
			abort();
		}
	}
}

#define NB_POINTS 1

void FSetVal(int OUT1[NB_POINTS], int val)
{
  int i;
  for (i = 0; i < NB_POINTS; i++)
    // oui, avec *0*, pas i
    SetVal(1, (int *) & OUT1[0], val);
}

void FAdd1(int IN1[NB_POINTS], int OUT1[NB_POINTS])
{
  int i;
  for (i = 0; i < NB_POINTS; i++) {
    // oui, avec *0*, pas i
    Add1(1, (int *) & IN1[0], (int *) & OUT1[0]);
  }
}

void FTest(int IN1[NB_POINTS], int res)
{
  int i;
  for (i = 0; i < NB_POINTS; i++)
    // oui, avec *0*, pas i
    Test(1, (int *) & IN1[0], res);
}

int main(int argc, char* argv[])
{
  int A[NB_POINTS], B[NB_POINTS];
  FSetVal(&A[0], 3);
  FAdd1(&A[0], &B[0]);
  FTest(&B[0], 4);
  return 0;
}
