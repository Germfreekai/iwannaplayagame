#include <stdio.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <sys/types.h> 
  
int main() { 
    char x = getchar();
    printf("Inserta un char (not really, suspende el proceso): %c", x);
} 