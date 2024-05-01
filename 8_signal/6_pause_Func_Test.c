#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void sig_handler(int sig)
{
    printf("Alarm TimeOut\r\n");
    exit(0);
}

int main (int argc, char *argv[])
{
    struct sigaction sig = {0};
    int second = 0;
    int ret = 0;
    sig.sa_handler = sig_handler;
    sig.sa_flags = 0;

    ret = sigaction(SIGALRM, &sig, NULL);
    if(ret < 0)
    {
        perror("sigaction Error");
        return 1;
    }

    second = atoi(argv[1]);
    printf("Timer : %d sec\r\n", second);
    alarm(second);


    /* Pause Function: Start */
    pause();
    puts("Sleep over");

    return 0;

}