#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
    int ret = 0;
    int fd;

    fd = open("./test.txt", O_WRONLY);
    if(fd < 0)
    {
        perror("Open Error");
        return 1;
    }

    ret = ftruncate(fd, 4 * 1024);
    if(ret < 0)
    {
        perror("Ftruncate Error");
        return 1;
    }
    close(fd);
    return 0;

}


