#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
    struct timespec request_t;
    puts("Sleep Start!");


    /*sleep 3sec*/
    request_t.tv_sec = 3;
    request_t.tv_nsec = 0;
    nanosleep(&request_t, NULL);
    puts("Sleep End!");
return 0;
}