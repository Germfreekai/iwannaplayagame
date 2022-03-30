#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>

// Msg functions
void WelcomePlayer(); 
void Explanation(); 

// Threads
void* TalkToUser(void* vargs);

// Signals
void signalHandler(int sig); 

int main(void)
{

	// Signals
	signal(SIGINT, signalHandler); 
	signal(SIGTERM, signalHandler); 

	WelcomePlayer(); 
	Explanation(); 

	while(1)
	{
		pause(); 
	}

	return EXIT_SUCCESS; 

}

void signalHandler(int sig)
{

	printf("%s", sig == 2 ? "You must think twice before leaving me\n" : sig == 15 ? "Alright... I am done with you\n" : "Bye\n"); 
	
	signal(SIGINT, signalHandler); 
	signal(SIGTERM, signalHandler); 

}

void* TalkToUser(void* vargs)
{

	char* msg = (char*)vargs; 

	for(size_t i = 0; i < strlen(msg); i++)
	{

		printf("%c", msg[i]); 
		fflush(stdout); 

		usleep(100000); 

	}

	pthread_exit(EXIT_SUCCESS); 

}

void WelcomePlayer()
{

	// Threads vars
	pthread_t ttu_t; 
	int ttu; 

	pthread_t ttu2_t; 
	int ttu2; 

	char* welcome_msg = "I wanna play a little game with you... "; 

	// Hostname
	int size = 200; 
	char* hostname = (char*)calloc(size,sizeof(char)); 
	gethostname(hostname, size); 

	ttu = pthread_create(&ttu_t, NULL, TalkToUser, (void*)welcome_msg); 
	pthread_join(ttu_t, NULL); 

	ttu2 = pthread_create(&ttu2_t, NULL, TalkToUser, (void*)hostname);
	pthread_join(ttu2_t, NULL); 

	printf("\n"); 
	
	free(hostname); 

}

void Explanation()
{

	pthread_t ttu_t; 
	int ttu; 

	char* explain = "I will make you some questions\nIf you fail to answer... you might face some consequences\n"; 

	ttu = pthread_create(&ttu_t, NULL, TalkToUser, (void*)explain); 
	pthread_join(ttu_t, NULL); 

	char* consequences = "There are three possible consequences...\n[1] You will drown in garbage\n[2] I will take away something from you\n[3] BOOM!\n"; 

	ttu = pthread_create(&ttu_t, NULL, TalkToUser, (void*)consequences); 
	pthread_join(ttu_t, NULL); 

}
