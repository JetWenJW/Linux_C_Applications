#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>



int main (void)
{
    int fd;
    int ret = 0;
    fd = open("./test.txt", O_RDONLY);
    if(fd < 0)
    {
        perror("Open Error");
        return 1;
    }
    ret = fcntl(fd, F_GETFL);
    if(ret < 0)
    {
        perror("fcntl Error");
        close(fd);
        return 1;
    }

    printf("flags: 0x%x\r\n", ret);

    ret = fcntl(fd, F_SETFL, ret | O_APPEND);
    if(ret < 0)
    {
        perror("fcntl Error");
        close(fd);
        return 1;
    }
    
    ret = fcntl(fd, F_GETFL);
    if(ret < 0)
    {
        perror("fcntl Error");
        close(fd);
        return 1;
    }

    printf("flags: 0x%x\r\n", ret);

    close(fd);
    return 0;  

}