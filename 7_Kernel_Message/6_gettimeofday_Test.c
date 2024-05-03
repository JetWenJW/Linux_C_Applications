#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

int main (void)
{
    struct timeval tval;
    int ret = 0;

    ret = gettimeofday(&tval, NULL);
    if(ret < 0)
    {
        perror("gettimeofday Error");
        return 1;
    }
    printf("time : %ld\r\n second, %ld\r\n ms", tval.tv_sec, tval.tv_usec);
    return 0;
}