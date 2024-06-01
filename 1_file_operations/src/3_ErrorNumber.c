#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main(void)
{
    int fd;
    printf("Errorno = %d\r\n", errno);
    fd = open("./test.txt",O_RDONLY);
    if(fd == -1)
    {
        printf("Errno = %d\r\n",errno);
        //printf("%s\r\n", strerror(errno));
        perror("open error");
        return 1;
    }
    return 0;
}