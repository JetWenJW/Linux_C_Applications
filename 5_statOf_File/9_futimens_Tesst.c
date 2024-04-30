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
    struct timespec tmsp_arr[2];
    int ret = 0;
    int fd;

    fd = open("./test.txt", O_RDONLY);
    if(fd < 0)
    {
        perror("Open Error");
        return 1;
    }

#if  0
    ret = futimens(fd, NULL);

#endif    

#if  0
    tmsp_arr[0].tv_nsec = UTIME_OMIT;
    tmsp_arr[1].tv_nsec = UTIME_NOW;
    ret = futimens(fd, tmsp_arr);
#endif

#if 1

    tmsp_arr[0].tv_nsec = UTIME_NOW;
    tmsp_arr[1].tv_nsec = UTIME_OMIT;
    ret = futimens(fd, tmsp_arr);
#endif

    if(ret < 0)
    {
        perror("futime Error");
        return 1;
    }
    close(fd);
    return 0;

}