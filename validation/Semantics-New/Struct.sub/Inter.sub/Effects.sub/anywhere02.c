#include <stdio.h>
#include <assert.h>


int N1 = 256;

int read_config_file()
{	static FILE* file = NULL;
	if (file == NULL)
		file = fopen("vals_init.txt","r");

	int r = fscanf(file, "%d", &N1);
	if (r == EOF)
	{
		fclose(file);
		return -1;
	}

	assert(0<=N1 && N1<=256  );
	return 0;
}


void main()
{
  read_config_file();
  
}

