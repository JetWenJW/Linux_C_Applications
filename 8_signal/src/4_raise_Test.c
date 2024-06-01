#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void sig_handler(int sig)
{
    printf("Received signal: %d\n", sig);
}


int main (int argc, char *argv[])
{
    struct sigaction sig = {0};
    int ret = 0;
    sig.sa_handler = sig_handler;
    sig.sa_flags = 0;

    ret = sigaction(SIGINT, &sig, NULL);
    if(ret < 0)
    {
        perror("sigaction Error");
        return 1;
    }

    while(1)
    {
        if(raise(SIGINT) != 0)
        {
            printf("Raise Error");
            return 1;
        }
        sleep(3);
    }

    return 0;
}