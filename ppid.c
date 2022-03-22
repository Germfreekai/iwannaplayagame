#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void* talk2Victim(void* vargs); 

int main(void)
{

	pid_t pid; 
	pid_t ppid; 

	pid = getpid(); 
	ppid = getppid(); 

	printf("On ppid My process number is: %d\n", pid); 
	printf("On ppid My parent's process number is: %d\n", ppid); 
	fflush(stdout); 

	int flag = 1; 
	while(flag)
	{

		if(kill(ppid, 0) == 0)
		{

			printf("Parent is still alive\n"); 
			fflush(stdout); 
		}
		else
		{

			fflush(stdout); 
			printf("You killed my parent!\n"); 
			fflush(stdout); 
		}

		sleep(1); 

	}

	return EXIT_SUCCESS; 

}
