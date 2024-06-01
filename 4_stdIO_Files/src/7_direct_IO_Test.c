#define  _GNU_SOURCE
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static char buf[4096] __attribute((aligned(4096)));

int main (void)
{
    int fd;
    int ret = 0;
    fd = open("directTest.txt", O_WRONLY | O_CREAT | O_EXCL | O_DIRECT , 0666);
    if(fd < 0)
    {
        perror("open error");
        return 1;
    }

    lseek(fd, 4096, SEEK_SET);

    for(int i = 0;i < 4096;i++)             /* 4096 * 4K = 16M bytes */
    {
        ret = write(fd, buf, sizeof(buf));
        if(ret < 0)
        {
            perror("write error");
            close(fd);
            return 1;
        }
    }

    close(fd);
    return 0;
}