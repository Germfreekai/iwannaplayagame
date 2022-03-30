#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void* slowPrint(void* vargs);

int main(int argc, char* argv[argc + 1])
{

	pthread_t sprint_t;
	int sprint;

	for(size_t i = 1; i < argc; i++)
	{
		
		pthread_create(&sprint_t, NULL, slowPrint, (void*)argv[i]);
		pthread_join(sprint_t, NULL); 
		printf(" "); 

	}

	printf("\n"); 

	return EXIT_SUCCESS; 

}

void* slowPrint(void* vargs)
{

	char* msg = (char*)vargs; 

	for(size_t i = 0; i < strlen(msg); i++)
	{

		printf("%c", msg[i]); 
		fflush(stdout); 
		usleep(100000); 

	}

	pthread_exit(NULL); 

}
