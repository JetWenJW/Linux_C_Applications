#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <utime.h>
#include <time.h>
#include <sys/time.h>


int main (void)
{

    int ret = 0;
    char buffer[128] = {0};

    ret = readlink("./sym_file", buffer, 128);
    if(ret < 0)
    {
        perror("readlink Error");
        return 1;
    }

    printf("readlink: %d \r\n", ret);
    printf("%s\r\n", buffer);

    return 0;

}