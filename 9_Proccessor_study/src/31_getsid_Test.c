#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main (void)
{
    printf("SID = %d\n", getsid(0));
    return 0;
}

