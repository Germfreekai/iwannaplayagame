#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{

	srand(time(NULL)); 

	int rnum = rand() % 30 + 1;

	printf("Num: %d\n", rnum);

	return EXIT_SUCCESS;

}
