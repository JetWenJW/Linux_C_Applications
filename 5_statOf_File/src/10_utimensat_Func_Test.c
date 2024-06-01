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


#if  1
    ret = utimensat(AT_FDCWD, "./test.txt",  tmsp_arr, 0);

#endif    

#if  0
    tmsp_arr[0].tv_nsec = UTIME_OMIT;
    tmsp_arr[1].tv_nsec = UTIME_NOW;
    ret = utimensat(AT_FDCWD, "./test.txt",  tmsp_arr, 0);
#endif

#if 1

    tmsp_arr[0].tv_nsec = UTIME_NOW;
    tmsp_arr[1].tv_nsec = UTIME_OMIT;
    ret = utimensat(AT_FDCWD, "./test.txt",  tmsp_arr, 0);
#endif

    if(ret < 0)
    {
        perror("futime Error");
        return 1;
    }
    return 0;

}