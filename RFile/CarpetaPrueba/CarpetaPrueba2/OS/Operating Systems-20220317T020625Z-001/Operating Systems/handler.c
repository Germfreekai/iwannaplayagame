#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t pidparent;
pid_t pidchild;
int opt;

void parenthandler(int numsig) {
    if(numsig==SIGINT) {
        printf("Parent process sending SIGINT\n");
        fflush(NULL);
        sleep(2);
    } else if(numsig==SIGUSR1) {
        printf("Parent process sending SIGUSR1\n");
        fflush(NULL);
        sleep(2);
    } else if(numsig==SIGUSR2) {
        printf("Parent process sending SIGUSR2\n");
        fflush(NULL);
        sleep(2);
    }
}

void childhandler(int numsig) {
    if(numsig==SIGINT) {
        kill(pidparent, SIGINT);
        printf("Child process sending SIGINT\n");
        fflush(NULL);
        sleep(2);
    } else if(numsig==SIGUSR1) {
        kill(pidparent, SIGUSR1);
        printf("Child process sending SIGUSR1\n");
        fflush(NULL);
        sleep(2);
    } else if(numsig==SIGUSR2) {
        kill(pidparent, SIGUSR2);
        printf("Child process sending SIGUSR2\n");
        fflush(NULL);
        sleep(2);
    }    
}

int main(void) {
    printf("Child process created.\n");    
    pidparent = getpid();
    pidchild = fork();

    
    if(pidchild!=0) {   // Parent process
        signal(SIGINT, parenthandler);
        signal(SIGUSR1, parenthandler);
        signal(SIGUSR2, parenthandler);
        
        printf("Pick a number from the following menu:\n");
        printf("1. SIGINT\n");
        printf("2. SIGUSR1\n");
        printf("3. SIGUSR2\n");
        printf("4. Exit\n");
        scanf("%d", &opt);
        
        while(opt < 4) {
            if(opt==1) {
                kill(pidchild, SIGINT);
                sleep(2);
            } else if(opt==2) {
                kill(pidchild, SIGUSR1);
                sleep(2);                
            } else if(opt==3) {
                kill(pidchild, SIGUSR2);
                sleep(2);                
            }
            printf("Pick a number from the following menu:\n");
            printf("1. SIGINT\n");
            printf("2. SIGUSR1\n");
            printf("3. SIGUSR2\n");
            printf("4. Exit\n");
            printf("Pick an option: ");
            scanf("%d", &opt); 
        }
        printf("Killing child process and exiting\n");
    } else {    // Child process
        signal(SIGINT, childhandler);
        signal(SIGUSR1, childhandler);
        signal(SIGUSR2, childhandler);
        while(1);
    }
    
    return 0;
}    