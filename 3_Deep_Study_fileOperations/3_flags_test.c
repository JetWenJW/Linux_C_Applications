#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


int main(void)
{
    int fd;
    fd = open("./test.txt", O_RDONLY | O_TRUNC);
    if(fd < 0)
    {
        perror("open Error");
        return 1;
    }
    close(fd);
    return 0;

}




