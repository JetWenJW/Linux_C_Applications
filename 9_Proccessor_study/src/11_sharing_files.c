#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>





int main(void)
{
    int fd = 0;
    fd = open("./test.txt", O_WRONLY | O_TRUNC);
    if( fd < 0)
    {
        perror("open Error");
        return 1;
    }

    switch(fork())
    {
        case -1:
            perror("fork Error");
            return 1;

        case 0:
            printf("Child\n");
            write(fd, "Hello world~", 12);
            close(fd);
            return 0;

        default:
            printf("Parent\n");
            write(fd, "JetWen", 6);
            close(fd);
            return 0;
    }
}

