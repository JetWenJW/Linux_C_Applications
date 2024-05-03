#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>


int main (void)
{
    int ret = 0;
    struct sysinfo info = {0};

    ret = sysinfo(&info);
    if(ret < 0 )
    {
        perror("Sysinfo Error");
        return 1;
    }

    printf("Uptime : %ld\n", info.uptime);
    printf("TotalRAM : %lu\n", info.totalram);
    printf("Free RAM : %lu\n", info.freeram);
    printf("Procs : %u\n", info.procs);
    return 0;
}