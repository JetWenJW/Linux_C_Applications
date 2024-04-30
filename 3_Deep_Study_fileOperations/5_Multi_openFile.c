#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


int main(void)
{
    int fd1;
    int fd2;
    fd1 = open("./test.txt", O_WRONLY | O_TRUNC | O_APPEND);
    if(fd1 < 0)
    {
        perror("open Error");
        return 1;
    }

    fd2 = open("./test.txt", O_WRONLY | O_APPEND);
    if(fd2 < 0)
    {
        perror("open Error");
        close(fd1);
        return 1;
    }

    write(fd1, "Hello World~", 12);
    write(fd2, "JetWen", 6);

    close(fd1);
    close(fd2);

    return 0;
}