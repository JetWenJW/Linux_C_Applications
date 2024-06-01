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
    FILE *file = NULL;
    int ret = 0;
    fd = open("./test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(fd < 0)
    {
        perror("open Error");
        return 1;
    }

    file = fdopen(fd, "w");
    if(file == NULL)
    {
        perror("fdopen Error");
        close(fd);
        return 1;
    }

    ret = fwrite("Hello World", 1, 11, file);
    if(ret < 11)
    {
        printf("fwrite Error or EOF\r\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}