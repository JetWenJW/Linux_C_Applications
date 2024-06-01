#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
    struct tm local_t;
    time_t sec;

    sec = time(NULL);
    if (-1 == sec) 
    {
        perror("time error");
        return 1;
    }
    printf("total seconds: %ld\n", sec);
    localtime_r(&sec, &local_t);


    printf("transfer get totalseconds: %ld\n", mktime(&local_t));
    return 0;

}