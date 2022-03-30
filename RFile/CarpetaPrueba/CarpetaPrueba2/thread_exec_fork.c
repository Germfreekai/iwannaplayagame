#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>

void* helloP(void* vargs);

int main(void)
{

	printf("Starting, we will create two threads\nEach thread will fork and execv two use hello program\n\n"); 

	// Definimos tipos
	pthread_t tid1;
	pthread_t tid2; 

	int tret1; 
	int tret2; 

	char* msg1 = "Rene"; 
	char* msg2 = "Marcela"; 

	tret1 = pthread_create(&tid1, NULL, helloP, (void*)&tid1);
	pthread_join(tid1, NULL); 

	sleep(3); 

	tret2 = pthread_create(&tid2, NULL, helloP, (void*)&tid2);
	pthread_join(tid2, NULL); 

	// Hacemos que el thread de main espere a los otros dos
	// con el join
	
	printf("Thread 1 returns: %d\nThread 2 returns: %d\n", tret1, tret2);

	printf("\n"); 

	return EXIT_SUCCESS;

}

void* helloP(void* vargs)
{
	//char* msg = (char*)vargs;
	int* myid = (int*)vargs;
	
	pid_t pid;

	// Hacamoe una copia del proceso actual
	// Me parece que por los threads, se harían 4
	pid = fork(); 

	if(pid == -1)
	{

		printf("Smth went wrong with FORK\n"); 

	}
	else if(pid == 0)
	{
		// El proceso hijo es el que sacrificamos
		char* args[] = {"./hello", "Rene", NULL};

		printf("Child: On thread %d before exec\n", *myid); 
		printf("Child: On thread %d, child pid: %u\n", *myid, getpid());
		printf("Child: On thread %d, parent pid: %u\n", *myid, getppid());

		if(execv(args[0], args) == 0)
		{
			printf("Smth went wrong on execv on thread\n"); 
		}

		exit(EXIT_SUCCESS);

	}
	else
	{
		wait(NULL); 

		printf("Parent, on thread %d, parent pid: %u\n", *myid, getpid());
		printf("Parent, on thread %d, parent parent pid: %u\n",*myid, getppid());

		printf("Success!\n"); 

	}

}
