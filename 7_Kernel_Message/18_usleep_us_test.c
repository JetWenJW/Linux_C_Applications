#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
    puts("Sleep Start!");

    /*sleep 3sec*/
    usleep(3 * 1000 * 1000);
    puts("Sleep End!");
    return 0;
    
}