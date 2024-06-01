#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void)
{
    switch(fork())
    {
        case -1:
            perror("fork Error");
            return 1;

        case 0:
            printf("Child, PID = %d\n", getpid());
            return 0;

        default:
        {
            int ret = 0;
            int status = 0;

            printf("Parent\n");
            ret = wait(&status);
            
            if(ret < 0)
            {
                perror("Parent\n");
                return 1;
            }

            printf("%d, %d\n", ret, WIFEXITED(status));
            return 0;
        }
    }
}