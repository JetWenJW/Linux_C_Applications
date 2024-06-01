
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
    int fd;
    char buffer[125];
    int ret = 0;

    memset(buffer, 0x00, sizeof(buffer));

    fd = open("./test.txt", O_RDONLY);
    if(fd < 0)
    {
        printf("open Error\r\n");
        return 1;
    }
    printf("Open Succeed~\r\n");

    ret = read(fd, buffer, 12);
    if(ret < 0)
    {
        printf("Read Error\r\n");
        close(fd);
        return 1;
    }
    printf("Read %d bytes : %s\r\n", ret, buffer);

    close(fd);
    return 0;
}