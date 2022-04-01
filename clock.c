#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

void* countDown(void* vargs); 
void* printsmth(void* vargs); 

int main(void)
{

	pthread_t timer_t; 
	int timer; 
	int flag; 


	timer = pthread_create(&timer_t, NULL, countDown, NULL); 
	pthread_join(timer_t, NULL); 
	
	printf("Thread prints %d\n", timer); 

	return EXIT_SUCCESS;


}

void* printsmth(void* vargs)
{
	printf("Hola\n"); 
	printf("Rene\n"); 

	return NULL; 

}

void* countDown(void* vargs)
{

	short sec; 
	sec = 30; 

	for(size_t i = 0; i < 31; i++)
	{

		printf("\r%02d", sec);
		sec--;
		fflush(stdout);
		sleep(1);

	}

	printf("\n"); 

	return NULL; 

}

