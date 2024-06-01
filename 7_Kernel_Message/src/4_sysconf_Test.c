#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main (void)
{
    printf("Proccessor Num : %ld\n", sysconf(_SC_CHILD_MAX));
    printf("System Tick : %ld\n", sysconf(_SC_CLK_TCK));
    printf("Page Size of Sys : %ld\n", sysconf(_SC_PAGESIZE));

    return 0;
}