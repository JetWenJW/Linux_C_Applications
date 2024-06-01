#define  _GNU_SOURCE
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    int fd;
    int ret = 0;
    FILE *file = fopen("./test.txt", "w");
    if(file == NULL)
    {
        perror("Open Error");
        return 1;
    }

    fd = fileno(file);
    if(fd < 0)
    {
        printf("fileno Error\r\n");
        fclose(file);
        return 1;
    }

    ret = write(fd, "hello World", 11);
    if(ret < 0)
    {
        perror("write Error");
        return 1;
    }

    fclose(file);
    return 0;
}