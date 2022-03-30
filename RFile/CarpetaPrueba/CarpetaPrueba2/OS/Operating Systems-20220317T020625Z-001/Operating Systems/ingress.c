// Operating Systems, Exam 3 (Problem 3)
// Marcela Fuentes (A01748161) & Blanca Agostini (A00517086)

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main() {
    int fd;
    char * myfifo = "/tmp/myfifo";
    char patient[100];

    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);

    /* receive the patient's name from the user */
    printf("Name of the patient: ");
    scanf("%[^\n]", patient);
    
    /* write the patient's name to the FIFO */
    fd = open(myfifo, O_WRONLY);
    write(fd, patient, sizeof(patient)+1);
    //close(fd);

    /* remove the FIFO */
    //unlink(myfifo);

    return 0;
}