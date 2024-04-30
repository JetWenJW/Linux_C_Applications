
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>


int main (void)
{

    int fd;
    int ret = 0 ;
    fd = open("./test.txt", O_WRONLY | O_CREAT | O_EXCL, 0644);
    if(fd == -1)
    {
        printf("Open Error\r\n");
        return 1;
    }

    printf("Open Succeed~\r\n");

    ret = write(fd, "Hello World~", 12); 
    if(ret < 0)
    {
        printf("Write Error~");
        close(fd);
        return 1;
    }

    printf("Write %d bytes\r\n", ret);
    close(fd);
    return 0;
}