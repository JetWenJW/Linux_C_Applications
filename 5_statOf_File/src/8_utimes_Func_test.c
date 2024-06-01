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
    struct timeval tmval_arr[2];
    time_t cur_sec;

    time(&cur_sec);
    for(int i = 0;i < 2;i++)
    {
        tmval_arr[i].tv_sec = cur_sec;
        tmval_arr[i].tv_usec = 0;
    }

    ret = utimes("./test.txt", tmval_arr);
    if(ret < 0)
    {
        perror("utimes error");
        return 1;
    }
    return 0;
}