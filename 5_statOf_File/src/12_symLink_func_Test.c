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
    int ret = 0;

    ret = symlink("./test.txt", "sym_file");
    if(ret < 0)
    {
        perror("symlink Error");
        return 1;
    }

    return 0;
}