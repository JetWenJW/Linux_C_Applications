#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>



int main (void)
{
    printf("PID: %d\n", getpid());
    return 0;
}

