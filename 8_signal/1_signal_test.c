#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>




static void sig_handler(int sig)
{
    printf("Received Signal: %d\n", sig);
}


int main (int argc, char *argv[])
{
    sig_t ret = NULL;
    ret = signal(SIGINT, (sig_t)sig_handler);
    if(SIG_ERR == ret)
    {
        perror("signal Error");
        return 1;
    }

    while(1)
    {
        sleep(1);
    }
    return 0;
}