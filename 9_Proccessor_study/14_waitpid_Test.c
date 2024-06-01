#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void)
{
    int pid = 0;
    pid = fork();
    switch(fork())
    {
        case -1:
            perror("fork Error");
            return 1;

        case 0:
            printf("Child, PID = %d\n", getpid());
            exit(0);

        default:
        {
            int ret = 0;
            int status = 0;

            printf("Parent\n");
            ret = waitpid(pid, &status, 0);
            
            if(ret < 0)
            {
                perror("Waitpid Error\n");
                return 1;
            }

            printf("%d, %d\n", ret, WEXITSTATUS(status));
            return 0;
        }
    }
}



