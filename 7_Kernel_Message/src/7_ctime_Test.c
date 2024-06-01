#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

int main (void)
{
    char tm_str[100] = {0};
    time_t tm;
    tm = time(NULL);
    if(tm < 0)
    {
        perror("ctime Error");
        return 1;
    }

    /* Transfer Data time to Date time */
    ctime_r(&tm, tm_str);

    printf("Now : %s", tm_str);

    return 0;

}