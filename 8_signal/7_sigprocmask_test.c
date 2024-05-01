#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void sig_handler(int sig)
{
    printf("SigHandler~~\r\n");
    exit(0);
}

int main (int argc, char *argv[])
{
    struct sigaction sig = {0};
    sigset_t    sig_set;
    int ret = 0;

    sig.sa_handler = sig_handler;
    sig.sa_flags = 0;

    ret = sigaction(SIGINT, &sig, NULL);
    if(ret < 0)
    {
        perror("sigaction Error");
        return 1;
    }

#if 0
    /* Initial sig set */
    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGINT);
    
    /* Add Signal to sig set */
    if(sigprocmask(SIG_BLOCK, &sig_set, NULL) == -1)
    {
        return 1;
    }

    /* Send SIGNAL to myself */
    raise(SIGINT);

    sleep(2);
    printf("Sleep Over\r\n");

    if(sigprocmask(SIG_BLOCK, &sig_set, NULL) == -1)
    {
        return 1;
    }
#endif

    while(1)
    {
        sleep(1);
        raise(SIGINT);
    }

    return 0;

}