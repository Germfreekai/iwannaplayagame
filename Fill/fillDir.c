#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

void* fillDir(void* vargs); 

int main(int argc, char* argv[argc+1])
{

	assert(argc == 2 && "Use ./FILE <n>");

	pthread_t fd_t; 
	int fd; 

	int nfiles = atoi(argv[1]);

	fd = pthread_create(&fd_t, NULL, fillDir, (void*)&nfiles);
	pthread_join(fd_t, NULL); 

	return EXIT_SUCCESS;

}

void* fillDir(void* vargs)
{

	int* nfiles = (int*)vargs;

	// Vars
	int length;
	char* nf; 
	char* fname;
	char* command; 

	for(int i = 1; i <= *nfiles; i++)
	{
		
		// Allocate mem for filename
		fname = (char*)calloc(20,sizeof(char));
		strcpy(fname, "notafile_");
		
		// Command
		command = (char*)calloc(20,sizeof(char));
		strcpy(command, "touch ");

		// Get size
		length = snprintf(NULL, 0, "%d", i);

		// Allocate one char more for null terminator
		nf = (char*)malloc(length + 1);

		// Add value to nf
		snprintf(nf, length + 1, "%d", i);
		
		// Make file name <file{n}>
		strcat(fname, nf);

		// Make command
		strcat(command, fname);

		system(command); 

		// Free mem
		free(fname);
		free(nf);
		free(command);

	}

	pthread_exit(EXIT_SUCCESS);

}
