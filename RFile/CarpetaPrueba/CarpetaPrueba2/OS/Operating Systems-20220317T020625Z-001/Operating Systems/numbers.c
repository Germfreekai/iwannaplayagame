// Operating Systems, Exam 3 (Problem 2)
// Marcela Fuentes (A01748161) & Blanca Agostini (A00517086)

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

int main(){
    
    int fileDescriptor=open("numbers.txt", O_CREAT | O_RDWR);
    ftruncate(fileDescriptor, sizeof(int)*20);
    int *c=(int*)mmap(NULL, sizeof(int)*20, PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, 0); 
    
    pid_t child = fork();
    
    if(child == 0){
        srand (time(NULL));
        int num;
        
        for(int i = 0; i < 5; i++){
            num = rand() % 100 + 1;
            c[i] = num;
        }
        
    }else{
       wait(NULL);
       printf("The numbers are ");
       
       for(int i = 0; i < 5; i++){
           printf("%d ", c[i]);
       }
       printf("\n");
    }
    return 0;
}