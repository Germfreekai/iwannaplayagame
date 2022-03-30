#include <stdio.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <sys/types.h> 
  
int main() { 
    int i; 
    int pid = fork(); 
  
    if (pid == 0) { 
        for (i=0; i<5; i++) 
            printf("I am a child\n"); 
    } else { 
        printf("I am a parent\n"); 
        while(1); 
    } 
} 