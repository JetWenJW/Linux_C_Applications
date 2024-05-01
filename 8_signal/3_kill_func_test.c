#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>




int main (int argc, char *argv[])
{

    int pid;
    if(argc < 2)
    {
        return 1;
    }

    pid = atoi(argv[1]);
    printf("pid %d\n", pid);

    if(kill(pid, SIGINT) < 0)
    {
        perror("Kill Error");
        return 1;
    }

    return 0;


}