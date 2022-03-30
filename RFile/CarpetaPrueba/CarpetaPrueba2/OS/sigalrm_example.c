#include <stdio.h>
#include <signal.h>

/*This is the Signal Handler */
void CatchAlarm(int sig_num){
    printf("\n Signal!!\n");
}

int main (){
    /* Set the ALRM signal handler to CatchAlarm */
    signal(SIGALRM, CatchAlarm);
    /* Start a 3s alarm */
    printf("\nSetting alarm for 3 seconds..\n");
    alarm(3);
    printf("\nWait for signal handling and press enter to finish program.\n");
    getchar();
    return 0;
}

