// Operating Systems, Exam 3 (Problem 3)
// Marcela Fuentes (A01748161) & Blanca Agostini (A00517086)

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUF 1024

int main() {
    int fd;
    char * myfifo = "/tmp/myfifo";
    char buf[MAX_BUF];

    /* open, read, and display the message from the FIFO */
    for(;;) {
        fd = open(myfifo, O_RDONLY);
        read(fd, buf, MAX_BUF);
        printf("Ingress: %s\n", buf);
        // close(fd);
    }
    
    return 0;
}