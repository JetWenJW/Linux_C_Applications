#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>




int main(void)
{
    int fd;
    int ret = 0;
    fd = open("./test.txt", O_WRONLY | O_APPEND);
    if(fd < 0)
    {
        perror("Open Error");
        return 1;
    }
    ret = write(fd, "Hello World~", 12);
    if(ret < 0)
    {
        perror("Write Error");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}