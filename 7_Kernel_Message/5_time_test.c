#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main (void)
{
    time_t t;

    t = time(NULL);
    if(t < 0)
    {
        perror("time Error");
        return 1;
    }
    printf("time : %d\n", (int)t);

}