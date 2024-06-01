#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <utime.h>
#include <time.h>



int main (void)
{

    int ret = 0;
    struct utimbuf times = {0};
    time_t cur_sec;

    time(&cur_sec);
    times.actime  = cur_sec;
    times.modtime = cur_sec;

    ret = utime("./test.txt", NULL);
    if(ret < 0)
    {
        perror("utime error");
        return 1;
    }
    return 0;
}