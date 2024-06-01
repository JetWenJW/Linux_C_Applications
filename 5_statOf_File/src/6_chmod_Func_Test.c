#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main (void)
{
    int ret = 0;

    ret = chmod("./test.txt", 0777);
    if(ret < 0)
    {
        perror("Chmod Error");
        return 1;

    }

    return 0;
}
