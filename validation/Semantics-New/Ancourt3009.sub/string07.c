/* Bug sent by Corinne, related to constant C strings. 
 *
 */

#include <stdio.h>
#include <string.h>

void testResult(char * filenameIn, char* fileNameOut)
{
	FILE *fichierIn, *fichierOut;
	char destination[40] = "";
	strcat(destination, filenameIn);
	fichierIn = fopen(destination, "r");
	if (fichierIn)
	  printf("*** Test OK - %s\n", destination);	
}

int main()
{
  testResult("./ref/module", "test.txt");
  return 0;
}
