#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (void)
{
    char *ptr = NULL;
    char str[] = "Hello Wrold~";

    ptr = strchr(str, 'W');
    if(ptr != NULL)
    {
        printf("Charater: %c\n", *ptr);
        printf("Offset: %d\n", (int)(ptr - str));
    }


    return 0;

}