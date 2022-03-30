#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{

	pid_t pid; 

	pid = fork(); 

	if(pid == -1)
	{

		printf("Fork failed\n"); 
		fflush(stdout); 

	}
	else if(pid == 0) // Proceso hijo
	{

		// Args
		char* args[] = {"./ppid", NULL, NULL}; 

		printf("On ppidParent, on child, parent process: %d\n", getppid()); 
		printf("On ppidParent, child process. %d\n", getpid()); 
		printf("just before exec\n"); 
		fflush(stdout); 

		if(execv(args[0], args) == 0)
		{

			printf("Execv failed\n"); 

		}

		exit(EXIT_SUCCESS); 

	}
	else
	{
		wait(NULL); 
		fflush(stdout); 		
		printf("On ppidParent, on parent, process: %d\n", getpid()); 
		printf("On ppidParent, on parent, parent process: %d\n", getppid()); 
		fflush(stdout); 

	}

}
