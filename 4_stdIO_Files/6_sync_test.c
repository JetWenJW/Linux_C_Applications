#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char buf[4096];

int main (void)
{
    int fd;
    fd = open("./sync.txt", O_WRONLY | O_CREAT | O_EXCL , 0666);
    if(fd < 0)
    {
        perror("Open Error");
        return 1;
    }

    for(int i = 0;i < 4096;i++)     /* 4096 *4k = 16M bytes */
    {
        write(fd, buf, sizeof(buf));
    }

    close(fd);

    return 0;
}

