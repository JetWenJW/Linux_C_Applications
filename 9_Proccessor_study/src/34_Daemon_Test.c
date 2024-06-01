#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

/*
 * The purpose of this program is creating a Daemon Processor
 */
int main (void)
{
    pid_t pid ;
    pid = fork();


    /* Step 1. Created A Child Proccessor & terminaated Parent Proccessor */
    if(pid == -1)
    {
        perror("fork Error");
        exit(0);
    }
    else if(pid < 0)
    {
        exit(0);
    }
    else if(pid == 0)
    {
        /* Step 2. Child Proccessor called setsid() Function Created a new set and be a new Set Leader */
        setsid();

        /* Stpe 3. Change work DIR to Root DIR */
        if(chdir("/") == -1)
        {
            perror("chdir Error");
            _exit(0);
        }

        /* Stpe 4. Reset umask  */
        umask(0);

        /* Step 5. Close has been opened fd */
        for(int i = 0;i < sysconf(_SC_OPEN_MAX);i++)
        {
            close(i);
        }

        /* Step 6. Ignore SIG_CHILD */
        if(signal(SIGCHLD, SIG_IGN) == SIG_ERR)
        {
            perror("signal Error");
            exit(1);
        }

        /* Finished The Daemon Task Created */
        while(1)
        {
            sleep(1);
        }
    }
}

