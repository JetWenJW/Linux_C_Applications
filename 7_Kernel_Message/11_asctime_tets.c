#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
    struct tm local_t;
    char tm_str[100] = {0};
    time_t sec;
    sec = time(NULL);
    if (-1 == sec) 
    {
        perror("time error");
        return 1;
    }
    localtime_r(&sec, &local_t);

    asctime_r(&local_t, tm_str);
    printf("localtime: %s", tm_str);
    
    return 0;
}