#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static unsigned char buf[4096];

int main (void)
{
    int fd;
    int ret = 0;
    fd = open("./test.txt", O_WRONLY | O_CREAT | O_EXCL, 0644);
    if(fd < 0)
    {
        perror("open error\r\n");
        return 1;
    }

    ret = lseek(fd, 4096, SEEK_SET);
    if(ret < 0)
    {
        perror("lseek error\r\n");
        close(fd);
        return 1;
    }

    ret = write(fd, buf, 4096);
    if(ret < 0)
    {
        perror("Write error\r\n");
        close(fd);
        return 1;
    }

    printf("write %d bytes\r\n", ret);
    close(fd);
    return 0;
}






