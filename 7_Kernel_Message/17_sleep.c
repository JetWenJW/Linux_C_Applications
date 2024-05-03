#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    puts("Sleep Start!");


    /* Sleep 3sec */
    sleep(3);
    puts("Sleep End!");
    exit(0);
}