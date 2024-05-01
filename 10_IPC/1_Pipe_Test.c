#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <string.h>


int main(void)
{

    int fds[2] = {0};

    if(pipe(fds) == -1)
    {
        perror("Pipe Error");
        exit(0);
    }

    switch (fork())
    {
        case -1:
            perror("fork Error");
            exit(0);

        case 0:
        {
            char rdbuf[64] = {0};
            printf("Child PID = %d\n", getpid());
            close(fds[1]);

            while(1)
            {
                read(fds[0], rdbuf, sizeof(rdbuf));
                printf("%s\n", rdbuf);
                memset(rdbuf, 0x0, sizeof(rdbuf));
            }
            _exit(0);
        }

        default :
            close(fds[0]);
            printf("Parent, PID = %d\n", getpid());
            
            while(1)
            {
                write(fds[1], "Hello Wrold~", 12);
                sleep(1);
            }
            
            break;    
    }

    exit(0);
    return 0;

}

