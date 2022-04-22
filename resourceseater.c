#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>

void signalHandler(int sig);
void* eatAll(void* vargs);

int main(int argc, char* argv[argc+1])
{

	// Deal with signals
	// SIGKILL can not be handled
	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);

	pthread_t pthread;

	while(1)
	{

		pthread_create(&pthread, NULL, eatAll, (void*)argv[0]);
	
	}

	return EXIT_SUCCESS;

}

void signalHandler(int sig)
{

	printf("%s", sig == 2 ? "Won't stop me like this...\n" : sig == 15 ? "Is that all you got?\n" : "Almost got me... but are you fast enough?");

	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);

}

void* eatAll(void* varg)
{

	char* name = (char*)varg;
	char* msg = " I am HUNGRY!!! \n";

	printf("%s", msg);

	pid_t pid = fork();

	if(pid == -1)
	{

		printf("Damn I failed my only purpose\n");

	}
	else if(pid == 0)
	{

		char* args[] = {name, NULL};

		printf("I am about to multiplicate! I need friends\n");

		// Make copy
		if(execv(args[0], args) == 0)
		{
			printf("I'm a dissappointment\n");

		}

		exit(EXIT_SUCCESS);

	}
	else
	{

		wait(NULL);

		printf("Are ok?\n");

	}

	return NULL;

}
