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
    int ret = 0;
    char buf[128] = {0};
    fd1 = open("./test.txt", O_RDWR | O_TRUNC );
    if(fd1 < 0)
    {
        perror("open Error");
        return 1;
    }

    fd2 = dup2(fd1, 1000);
    if(fd2 < 0)
    {
        perror("Dup Error");
        close(fd1);
        return 1;
    }

    printf("fd2: %d\r\n", fd2);

    ret = write(fd1, "Hello World~", 12);
    if(ret < 0)
    {
        perror("write Error");
        close(fd1);
        close(fd2);
        return 1;
    }

    lseek(fd1, 0, SEEK_SET);

    ret = read(fd1, buf, 12);
    if(ret < 0)
    {
        perror("read Error");
        close(fd1);
        close(fd2);
        return 1;
    }
    printf("read :%s \r\n", buf);


    close(fd1);
    close(fd2);

    return 0;
}