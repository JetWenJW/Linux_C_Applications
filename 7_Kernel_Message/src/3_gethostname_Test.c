#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>




int main (void)
{
    char hostname[20];
    int ret = 0;

    memset(hostname, 0, sizeof(hostname));
    ret = gethostname(hostname, sizeof(hostname));
    if(ret < 0)
    {
        perror("gethostname Error");
        return 1;
    }

    puts(hostname);
    return 0;
}