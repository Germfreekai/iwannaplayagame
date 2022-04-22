#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void signalHandler(int sig);
void ResourceEater(); 
void* eatAll(void* vargs);

int main(void)
{

	// Signals
	signal(SIGINT, signalHandler); 
	signal(SIGTERM, signalHandler); 

	int flag = 1;
	
	// Get PID from another process
	char pidline[1024]; 
	char* pid; 

	FILE* fp = popen("pidof iwannaplayagame", "r"); 
	fgets(pidline, 1024, fp); 

	int p = atoi(pidline); 

	while(flag)
	{

		// Check for father
		if(kill(p,0) == 0)
		{

			fflush(stdout);

		}
		else
		{

			fflush(stdout);
			printf("\nWhat have you done?\nI will revenge my father!!!\n");
			fflush(stdout);

			flag = 0;
		}

		sleep(1);

	}

	ResourceEater();

	return EXIT_SUCCESS;

}

void signalHandler(int sig)
{

	printf("I am not as patient as my father, now.... bye!\n"); 

	ResourceEater(); 

	// Kill 
	//
	// exit(2); 
}

void ResourceEater()
{

	pthread_t pthread;

	while(1)
	{

		pthread_create(&pthread, NULL, eatAll, (void*)argv[0]);
	
	}

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
