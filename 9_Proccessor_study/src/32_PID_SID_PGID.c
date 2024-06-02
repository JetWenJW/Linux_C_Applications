#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main (void)
{
    switch(fork())
    {
        case -1 :
            perror("fork Error");
            return 1;
        
        case 0 :
            printf("Child PID = %d, PGID = %d, SID = %d\n", getpid(), getpgid(0), getsid(0));

            _exit(0);

        default :
            printf("Parent PID = %d, PGID = %d, SID = %d\n", getpid(), getpgid(0), getsid(0));
            break;
    }

    exit(0);
    return 0;
}