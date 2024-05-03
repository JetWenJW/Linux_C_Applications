#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

int main (void)
{
    struct tm t;
    time_t sec;
    sec = time(NULL);
    if(sec < 0)
    {
        perror("time Error");
        return 1;
    }

    localtime_r(&sec, &t);

    printf("Now: %d 年%d 月%d 日 %d:%d:%d\n",
            t.tm_year + 1900, t.tm_mon, t.tm_mday,
            t.tm_hour, t.tm_min, t.tm_sec);

return 0;
}