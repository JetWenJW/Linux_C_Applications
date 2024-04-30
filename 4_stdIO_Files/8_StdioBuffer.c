//#define  _GNU_SOURCE
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{

    printf("Hello World 1\r\n");
    printf("Hello World 2");

    //fflush(stdout);
    fclose(stdout);
    while(1)
    {
        sleep(1);
    }

    return 0;
}
