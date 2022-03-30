#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{

	// Null terminated array of chars
	char* args[] = {"../Forks/addtwo", "7", "4", "5", NULL};

	// Llmamaos el proceso a invocar y el arreglo
	execv(args[0],args);

	// Everything is ignonred after EXECVP()
	// as this process is replaced by another one
	
	printf("ending--------\n");

	return EXIT_SUCCESS;

}
