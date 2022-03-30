// Operating Systems, Exam 3 (Problem 1)
// Marcela Fuentes (A01748161) & Blanca Agostini (A00517086)

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf{
    long mtype;
    char mtext[40];
};

int main(){
    key_t key = ftok("/home/ec2-user/environment/key.txt", 13);
    int mailbox = msgget(key, IPC_CREAT|0666);
    struct msgbuf m;
    int value = msgrcv(mailbox, &m, sizeof(struct msgbuf), 0, IPC_NOWAIT);
    if(value == -1){
        printf("There are not any more orders. You can take a break\n");
    }else{
        printf("The next order to attend is %s\n", m.mtext);
    }
}