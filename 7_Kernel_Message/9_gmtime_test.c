#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
    struct tm local_t;
    struct tm utc_t;
    time_t sec;
    /* 获取时间 */
    sec = time(NULL);
    if (0 > sec) 
    {
        perror("time error");
        return 1;
    }
    localtime_r(&sec, &local_t);
    
    gmtime_r(&sec, &utc_t);

    printf("本地时间: %d 年%d 月%d 日 %d:%d:%d\n",
            local_t.tm_year + 1900, local_t.tm_mon, local_t.tm_mday,
            local_t.tm_hour, local_t.tm_min, local_t.tm_sec);
    
    printf("UTC 时间: %d 年%d 月%d 日 %d:%d:%d\n",
            utc_t.tm_year + 1900, utc_t.tm_mon, utc_t.tm_mday,
            utc_t.tm_hour, utc_t.tm_min, utc_t.tm_sec);

    return 0;
}