#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (void)
{
    char *ptr = NULL;
    char str[] = "I lovs my home";

    ptr = strstr(str, "home");
    if(ptr != NULL)
    {
        printf("Charater: %c\n", *ptr);
        printf("Offset: %d\n", (int)(ptr - str));
    }


    return 0;

}