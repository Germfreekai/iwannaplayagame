#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getName(char* arg); 

int main(int argc, char* argv[argc + 1])
{

	char* rname = getName(argv[0]); 

	printf("File name: %s\n", rname); 

	free(rname); 

	return EXIT_SUCCESS;

}

char* getName(char* arg)
{

	char* fname = arg; 
	char* rname = (char*)calloc(15, sizeof(char)); 

	size_t s = 0; 

	for(size_t i = strlen(fname)-1; i > 0; i--)
	{

		if(fname[i] == '/')
		{

			s = i; 

		}

	}

	int c = 0; 

	for(size_t i = s + 1; i < strlen(fname); i++)
	{

		rname[c] = fname[i]; 

		c++; 

	}

	return rname; 

}
