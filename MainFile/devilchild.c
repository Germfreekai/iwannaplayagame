#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void signalHandler(int sig);

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

	return EXIT_SUCCESS;

}

void signalHandler(int sig)
{

	printf("I am not as patient as my father, now.... bye!\n"); 

	// Kill 
	//
	exit(2); 
}
