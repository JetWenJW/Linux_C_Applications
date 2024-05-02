#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main (void)
{
    switch(fork())
    {
        case -1 :
            perror("vfork Error");
            return 1;
        
        case 0 :
            printf("Child PID = %d, PGID = %d\n", getpid(), getpgid(0));
            if(-1 == setpgrp())
            {
                perror("setpgrp Error");
                return 1;
            }





            printf("PGID = %d\n", getpgrp());
            printf("\n");
            _exit(0);

        default :
            printf("Parent PID = %d, PGID = %d\n", getpid(), getpgid(0));
            break;
    }


    exit(0);
    return 0;
}