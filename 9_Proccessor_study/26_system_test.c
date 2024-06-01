#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main (void)
{
    int ret = -1;

    ret = system("ls -al");
    if(ret == -1)
    {
        perror("system Error");
        return 1;
    }
    printf("%d \n", WIFEXITED(ret));
    return 0;

}